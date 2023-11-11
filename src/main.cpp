/*
  File: 
   main.cpp

  Version: 
   V0.1

  Program Description: 
    A rendition of the Top program using C++. It has been tested on Ubuntu and
    Arch Linux.  Most if not all the current features should work on other Linux
    distributions.

  Controls:
  - the 'x' key allows highlighting a particular column.
  - the arrow keys allow shifting the windows left and right.
  - the '<' and '>' keys change how the columns are sorted.
  - the 'k' key allows the user to "kill" desired processes.
*/
#include <algorithm>
#include <chrono>
#include <climits>
#include <cmath>
#include <ctime>
#include <dirent.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <ncurses.h>
#include <pwd.h>
#include <unordered_map>
#include <unistd.h>
#include <set>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/param.h>
#include "_cursesWinConsts.hpp"
#include "_fileConsts.hpp"
#include "_progStateConsts.hpp"
#include "byteConverter.hpp"
#include "changeProgramStates.hpp"
#include "cpuInfo.hpp"
#include "cursesFunctions.hpp"
#include "cursesWindow.hpp"
#include "extractFileData.hpp"
#include "log.hpp"
#include "memInfo.hpp"
#include "processInfo.hpp"
#include "secondsToTime.hpp"
#include "sortProcessLists.hpp"
#include "taskInfo.hpp"

#include <iterator>
#include <sstream>

// debug constants
#define _CURSES 1
#define _LOG 1



/*
  Function:
   main

  Description:
   The main driver function for the Bottom program.
*/
int main()
{
  //  ## create log system ##
  time_t rawtime;
  struct tm* timeinfo;
#if _LOG    
  Log logFile("./log/", "log", 1, ".log");
  std::ofstream log;

  //  get time info
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  // open log file
  while(true)
    {
      std::ifstream inFile(logFile.getFullPath(), std::ifstream::in);
      
      // check if log exists      
      if(inFile.is_open())
	{
	  // increment the log number and close the open file
	  logFile.incrementFileName();
	  inFile.close();
	}
      // log doesn't exist, create the new log file
      else
	{
	  log.open(logFile.getFullPath());
	  break;
	}
    }

  // check if the file remained open, exit with error otherwise
  if(!log.is_open())
    {
      std::cerr << "Error creating log file." << std::endl;
      exit(EXIT_FAILURE);
    }
  else
    {
      // output start of log session
      log << "LOG Started" << std::endl;
      log << "Time and Date: " << asctime(timeinfo) << std::endl;
    }
#endif
  // process related vars
  MemInfo memInfo;
  CPUInfo cpuInfoStart;
  CPUInfo cpuInfoEnd;
  CPUUsage cpuUsage;
  TaskInfo taskInfo;
  ProcessInfo* process;
  std::vector<int> pids; // all currently allocated process PIDs
  std::vector<int> pidsOld; // previously found active PID
  std::vector<int> pidsDead; // PIDs that closed during loop
  std::unordered_map<int, ProcessInfo*> allProcessInfo; // /proc/[pid]/ data
  
  // window related vars
  std::unordered_map<int, CursesWindow*> allWins;
  
  // state related vars
  int progState = 0;
  int prevState = 0;
  int sortState = _PROCCPUWIN;
  bool highlight = false;
  bool quit = false;
  int shiftY = 1;
  int shiftX = _PIDWIN;
  bool graph = false;
  std::unordered_map<char, int> progStates;

#if _CURSES    
  // ## initialize and setup curses ##
  initializeCurses();
#endif
  initializeStartingWindows(allWins);
  defineStartingWindows(allWins);
  initializeProgramStates(progStates);
  
  // loop variables
  SecondsToTime uptime;
  std::vector<std::string> allTopLines;
  std::vector<std::string> loadAvgStrings;
  std::vector<std::string> uptimeStrings;
  std::string filePath;
  std::string colorLine;
  std::string timeString;
  int outerInterval = 1000000;
  bool newOuterInterval = true;

  auto startTime = std::chrono::high_resolution_clock::now();

  do{
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    pidsOld = pids;
    pids.clear();
    process = nullptr;
    loadAvgStrings.clear();
    uptimeStrings.clear();
    allTopLines.clear();

    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>
      (currentTime - startTime).count();

    if(newOuterInterval == true)
      {
	// extract start data for CPU line
	// "%Cpu(s): x.x us, x.x sy..."
	extractProcStat(cpuInfoStart,
			_PROC_STAT);
	newOuterInterval = false;
      }

    if(elapsedTime >= outerInterval)
      {
	// extract end data for CPU line
	extractProcStat(cpuInfoEnd,
			_PROC_STAT);

	// calculate cpu averages
	cpuUsage = calcCPUUsage(cpuInfoStart,
				cpuInfoEnd);
	
	startTime = currentTime;
	newOuterInterval = true;
      }
    
    // get current active PIDS
    pids = findNumericDirs(_PROC);

    // find any processes that died during previous loop
    if(findDeadProcesses(pids, pidsOld, pidsDead))
      {
	// free if any found
	removeDeadProcesses(allProcessInfo, pidsDead);
      }

    // extract data from /proc/uptime for very top window
    // "current time, # users, load avg"    
    extractProcUptime(uptime,
		      uptimeStrings,
		      _PROC_UPTIME);

    // extract data from /proc/loadavg for very top window
    extractProcLoadavg(loadAvgStrings,
		       _PROC_LOADAVG);

    // extract data for MiB Mem and MiB swap
    // "MiB Mem: xxxx.xx total, xxxx.xx Free..."
    extractProcMeminfo(memInfo,
		       _PROC_MEMINFO);    

    // set the time string with current military time
    timeString = uptime.returnHHMMSS(timeinfo->tm_hour,
				     timeinfo->tm_min,
				     timeinfo->tm_sec);

    // create the top lines for ouput
    allTopLines.push_back(createTopLine(timeString,
					uptime.getHours()/24,
					uptime.getHours() % 24,
					uptime.getMinutes(),
					loadAvgStrings));
    defineTasksLine(allTopLines);
    defineCpusLine(allTopLines);
    defineMemMiBLine(allTopLines);
    defineMemSwapLine(allTopLines);
    
    // update/add process data for still running and new found processes
    for(int i = 0; i < pids.size(); i++)
      {
	// if new process was found, allocate it
	if(allProcessInfo.count(pids.at(i)) == 0)
	  {
	    process = new ProcessInfo();
	    allProcessInfo.insert(std::make_pair(pids.at(i), process));
	  }
	
	// set pid of current process
	allProcessInfo.at(pids.at(i))->setPID(pids.at(i));

	// extract per process data (USER, PR, VIRT...)
	// /proc/[pid]/status
	filePath.clear();
	filePath = _PROC + std::to_string(pids.at(i));
	filePath.append(_STATUS);
	extractProcPidStatus(allProcessInfo,
			     pids.at(i),
			     filePath);
	
	// /proc/uptime & /proc/[pid]/stat
	filePath.clear();
	filePath = _PROC + std::to_string(pids.at(i));
	filePath.append(_STAT);
	extractProcPidStat(allProcessInfo,
			   memInfo,
			   uptime,
			   pids.at(i),
			   uptimeStrings,
			   filePath);

	// extract COMMAND
	// /proc/[pid]/comm
	filePath.clear();
	filePath = _PROC + std::to_string(pids.at(i));
	filePath.append(_COMM);
	extractProcPidComm(allProcessInfo,
			   pids.at(i),
			   filePath);
      }
    
    // count the extracted process states for task window
    // "Tasks: XXX total, X running..."
    countProcessStates(allProcessInfo,
		       taskInfo);

    // ## get user input ##
    std::vector<int> outPids;
    int userInput = 0;

    userInput = getch();

    // check for user input
    if(userInput != -1)
      {
	// update program state
	if(progStates[userInput])
	  {
	    prevState = progState;
	    progState = userInput;
	  }
	// undefined input
	else 
	  {
	    std::string outString = " Unknown command - try 'h' for help ";
#if _CURSES
	    printBadInputString(allWins,
				_MAINWIN,
				_YOFFSET - 1,
				0,
				outString);
	    refreshAllWins(allWins);
	    doupdate();
	    sleep(1.75);
#endif
	  }
      }
    
    flushinp();

#if _CURSES
    // ## update states ##
    // update process sort state (changed by '<' and '>' user input)
    updateSortState(allProcessInfo,
		    pids,
		    outPids,
		    sortState);
    
    // program state
    updateProgramState(allProcessInfo,
		       allWins,
		       progState,
		       prevState,
		       sortState,
		       quit,
		       highlight,
		       outPids.at(0),
		       shiftY,
		       shiftX,
		       outPids.size() - 2,
		       graph);

    // ## print process windows ##
    if(highlight == true)
      {
	wattron(allWins.at(sortState)->getWindow(),
		A_BOLD);
      }
    else
      {
	wattroff(allWins.at(sortState)->getWindow(),
		 A_BOLD);
      }
    if(graph == true)
      {
	box(allWins.at(_CPUGRAPHWIN)->getWindow(), 'a', 'a');
      }
    
    updateWindowDimensions(allWins);
    colorLine = createColorLine(allWins.at(_MAINWIN)->getNumCols());    
    clearAllWins(allWins);
    printTopWins(allWins,
		 allTopLines);
    boldOnAllTopWins(allWins,
		     A_BOLD);
    printTasksData(allWins,
		   taskInfo);
    printCpusData(allWins,
		  cpuUsage);
    printMemMiBData(allWins,
		    memInfo);
    boldOffAllTopWins(allWins,
		      A_BOLD);
    printProcs(allWins,
	       allProcessInfo,
	       outPids,
	       shiftY,
	       shiftX);
    attronBottomWins(allWins,
		     _BLACK_TEXT);
    printWindowNames(allWins);
    attroffBottomWins(allWins,
		      _BLACK_TEXT);
    printLine(allWins,
	      _YOFFSET,
	      0,
	      _BLACK_TEXT,
	      _MAINWIN,
	      colorLine);
    refreshAllWins(allWins);
    doupdate();
#endif

    if(quit)
      {
	break;
      }

  } while(true);

  // cleanup
  for(std::unordered_map<int, ProcessInfo*>::iterator it = allProcessInfo.begin();
      it != allProcessInfo.end(); it++)
    {
      delete(it->second);
      it->second = nullptr;
    }
  
  allProcessInfo.clear();


#if _LOG
  if(log.is_open())
    {
      log.close();
    }
#endif
#if _CURSES  
  endwin();
#endif
  
  return 0;
} // end of "main"
