/*
  File: 
   main.cpp

  Program Description: 
    A rendition of the Top program using C++. It has been tested on Ubuntu and
    Arch Linux. However, most if not all the current features should work on
    other Linux distributions.
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
#include <queue>
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
  std::vector<int> pidsStartOld;
  std::vector<int> pidsEndOld;
  std::vector<int> pidsStart;
  std::vector<int> pidsEnd;
  std::vector<int> pidsStartDead;
  std::vector<int> pidsEndDead;
  std::set<std::string> users;
  int numUsers;
  std::unordered_map<int, ProcessInfo*> procInfoStart;
  std::unordered_map<int, ProcessInfo*> procInfoEnd;
  
  // window related vars
  std::unordered_map<int, CursesWindow*> allWins;
  std::string colorLine;
  
  // state related vars
  int progState = 0;
  int prevState = 0;
  int sortState = _PROCCPUWIN;
  bool highlight = false;
  bool quit = false;
  int shiftY = 1;
  int shiftX = _PIDWIN;
  bool cpuGraph = true;
  std::unordered_map<char, int> progStates;

#if _CURSES    
  // ## initialize and setup curses ##
  initializeCurses();
#endif
  initializeStartingWindows(allWins);
  defineStartingWindows(allWins);
  initializeProgramStates(progStates);

  // graph related vars
  std::queue<double> cpuUsageVals;
  const int cpuGraphMaxLines = ((allWins.at(_MAINWIN)->getNumLines() - _YOFFSET)/2) - 2;
  const int cpuGraphMaxCols = allWins.at(_MAINWIN)->getNumCols() -
    allWins.at(_COMMANDWIN)->getNumCols() - 2;
  int cpuGraphCount = 0;
  
  // loop variables
  SecondsToTime uptime;
  std::vector<std::string> allTopLines;
  std::vector<std::string> loadAvgStrings;
  std::vector<std::string> uptimeStrings;
  std::string filePath;
  std::string timeString;
  std::vector<int> outPids;
  int interval = 1000000;
  bool newInterval = true;
  bool entered = false;
  bool stateChanged = false;
  auto startTime = std::chrono::high_resolution_clock::now();

  do{
    users.clear();
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    loadAvgStrings.clear();
    uptimeStrings.clear();
    allTopLines.clear();
    outPids.clear();

    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>
      (currentTime - startTime).count();

    // erase extracted process data and reset interval if state was changed to
    // prevent printing incorrect CPUUsage calculation
    if(stateChanged == true)
      {
	currentTime = std::chrono::high_resolution_clock::now();
	elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>
	  (currentTime - startTime).count();

	for(std::unordered_map<int, ProcessInfo*>::iterator
	      it = procInfoStart.begin();
	    it != procInfoStart.end(); it++)
	  {
	    delete(it->second);
	    it->second = nullptr;
	  }
	for(std::unordered_map<int, ProcessInfo*>::iterator it
	      = procInfoEnd.begin();
	    it != procInfoEnd.end(); it++)
	  {
	    delete(it->second);
	    it->second = nullptr;
	  }

	procInfoEnd.clear();
	procInfoStart.clear();
	
	stateChanged = false;
	entered = false;
	newInterval = true;
      }
    
    if(newInterval == true)
      {
	// extract start data for CPU line
	// "%Cpu(s): x.x us, x.x sy..."
	extractProcStat(cpuInfoStart,
			_PROC_STAT);
      }
    else if(elapsedTime >= interval)
      {
	// extract end data for CPU line
	extractProcStat(cpuInfoEnd,
			_PROC_STAT);

	// calculate cpu averages
	cpuUsage = calcCPUUsage(cpuInfoStart,
				cpuInfoEnd);

	// store cpu utilization in queue for graph output
	if(cpuUsageVals.empty() || cpuUsageVals.size() < (cpuGraphMaxCols/2) + 1)
	  {
	    cpuUsageVals.push(cpuUsage.utilization);
	  }
	else
	  {
	    cpuUsageVals.pop();
	    cpuUsageVals.push(cpuUsage.utilization);
	  }	
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

    if(newInterval == true)
      {
	// get starting pids
	pidsStartOld.clear();
	pidsStartOld = pidsStart;
	pidsStart.clear();
	pidsStartDead.clear();
	pidsStart = findNumericDirs(_PROC);

	// find if any start interval pids died since last interval
	if(findDeadProcesses(pidsStart, pidsStartOld, pidsStartDead))
	  {
	    removeDeadProcesses(procInfoStart, pidsStartDead);
	  }

	// extract per process data
	extractProcessData(procInfoStart,
			   pidsStart,
			   memInfo,
			   uptime,
			   uptimeStrings,
			   users);
	numUsers = users.size();

	// set interval flag
	newInterval = false;
      }    
    else if(elapsedTime >= interval)
      {
	// get end interval pids
	pidsEndOld.clear();
	pidsEndOld = pidsEnd;
	pidsEnd.clear();
	pidsEndDead.clear();
	pidsEnd = findNumericDirs(_PROC);

	// find if any end interval pids died since last interval
	if(findDeadProcesses(pidsEnd, pidsEndOld, pidsEndDead))
	  {
	    removeDeadProcesses(procInfoEnd, pidsEndDead);
	  }
	
	// extract per process data
	extractProcessData(procInfoEnd,
			   pidsEnd,
			   memInfo,
			   uptime,
			   uptimeStrings,
			   users);
	numUsers = users.size();

	// find if any process data changed and calc per process cpu usage
	for(int i = 0; i < pidsEnd.size(); i++)
	  {
	    for(int j = 0; j < pidsStart.size(); j++)
	      {
		if(pidsEnd.at(i) == pidsStart.at(j))
		  {
		    procInfoEnd.at(pidsEnd.at(i))->
		      calcProcCPUUsage(*procInfoStart.at(pidsStart.at(j)),
				       *procInfoEnd.at(pidsEnd.at(i)));
		    procInfoStart.at(pidsStart.at(j))->
		      setCPUUsage(procInfoEnd.at(pidsEnd.at(i))->getCPUUsage());
		  }
	      }
	  }

	// set flags and update the new start time for interval
	entered = true;	
	newInterval = true;
	startTime = currentTime;
      }
    
    // count the extracted process states for task window
    // "Tasks: XXX total, X running..."
    countProcessStates(procInfoEnd,
		       taskInfo);

    // set the time string with current military time
    timeString = uptime.returnHHMMSS(timeinfo->tm_hour,
				     timeinfo->tm_min,
				     timeinfo->tm_sec);

    // create the top lines for ouput
    allTopLines.push_back(createTopLine(timeString,
					uptime.getHours()/24,
					uptime.getHours() % 24,
					uptime.getMinutes(),
					loadAvgStrings,
					numUsers));
    defineTasksLine(allTopLines);
    defineCpusLine(allTopLines);
    defineMemMiBLine(allTopLines);
    defineMemSwapLine(allTopLines);

    // ## get user input ##
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

#if _CURSES    
    flushinp();

    // ensure to not clear the windows if entering certain states    
    if(userInput != _STATEKILL)
      {
	clearAllWins(allWins);
      }

    // draw cpu graph
    if(cpuGraph == true)
      {

	drawGraph(allWins,
		  _CPUGRAPHWIN,
		  cpuUsageVals,
		  "CPU UTILIZATION");
      }

    updateWindowDimensions(allWins);
    colorLine = createColorLine(allWins.at(_MAINWIN)->getNumCols());
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
    // ## update states and print ##
    if(entered == false)
      {
	updateSortState(procInfoStart,
			pidsStart,
			pidsStart,
			sortState);
	updateProgramState(procInfoStart,
			   allWins,
			   progState,
			   prevState,
			   sortState,
			   quit,
			   highlight,
			   pidsStart.at(0),
			   shiftY,
			   shiftX,
			   pidsStart.size() - 2,
			   cpuGraph,
			   stateChanged,
			   cpuGraphCount);
	printProcs(allWins,
		   procInfoStart,
		   pidsStart,
		   shiftY,
		   shiftX,
		   sortState,
		   highlight);		   
	colorOnBottomWins(allWins,
			  _BLACK_TEXT);
	printWindowNames(allWins);
	colorOffBottomWins(allWins,
			   _BLACK_TEXT);    
	printLine(allWins,
		  _YOFFSET,
		  0,
		  _BLACK_TEXT,
		  _MAINWIN,
		  colorLine);    
      }
    else if(stateChanged == false)
      {
	updateSortState(procInfoEnd,
			pidsEnd,
			outPids,
			sortState);
	updateProgramState(procInfoEnd,
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
			   cpuGraph,
			   stateChanged,
			   cpuGraphCount);
	printProcs(allWins,
		   procInfoEnd,
		   outPids,
		   shiftY,
		   shiftX,
		   sortState,
		   highlight);
      }
    
    colorOnBottomWins(allWins,
		      _BLACK_TEXT);
    printWindowNames(allWins);
    colorOffBottomWins(allWins,
		       _BLACK_TEXT);    
    printLine(allWins,
	      _YOFFSET,
	      0,
	      _BLACK_TEXT,
	      _MAINWIN,
	      colorLine);
    refreshAllWins(allWins);
    doupdate();
    usleep(50000);
#endif

    if(quit)
      {
	break;
      }
    
  } while(true);

  // cleanup
  for(std::unordered_map<int, ProcessInfo*>::iterator it
	= procInfoStart.begin();
      it != procInfoStart.end(); it++)
    {
      delete(it->second);
      it->second = nullptr;
      
    }
  for(std::unordered_map<int, ProcessInfo*>::iterator it
	= procInfoEnd.begin();
      it != procInfoEnd.end(); it++)
    {
      delete(it->second);
      it->second = nullptr;
      
    }
  
  procInfoEnd.clear();
  procInfoStart.clear();

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
