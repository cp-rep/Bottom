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
  std::unordered_map<int, CursesWindow*> wins;
  std::string colorLine;
  int numLines;
  int numCols;
  
  // state related vars
  int progState = 0;
  int prevState = 0;
  int sortState = _PROCCPUWIN;
  bool highlight = false;
  bool quit = false;
  int shiftY = 1;
  int shiftX = _PIDWIN;
  std::unordered_map<char, int> progStates;

#if _CURSES    
  // ## initialize and setup curses ##
  initializeCurses();
#endif
  initializeStartingWindows(wins);
  defineProcWinsStartVals(wins);
  defineTopWinsStartVals(wins);  
  defineTopWinsDataStartVals(wins);
  defineGraphWinStartVals(wins);
  initializeProgramStates(progStates);

  // graph related vars
  std::queue<double> cpuUsageVals;
  std::queue<double> memUsageVals;
  int cpuGraphCount = 1;
  int memGraphCount = 1;
  
  // loop variables
  SecondsToTime uptime;
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
    getmaxyx(stdscr, numLines, numCols);
    const int graphMaxCols = numCols - wins.at(_COMMANDWIN)->getNumCols();
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
	users.clear();
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	loadAvgStrings.clear();
	uptimeStrings.clear();
	// extract start data for CPU line
	// "%Cpu(s): x.x us, x.x sy..."
	extractProcStat(cpuInfoStart,
			_PROC_STAT);
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
	// count the extracted process states for task window
	// "Tasks: XXX total, X running..."
	countProcessStates(procInfoStart,
			   taskInfo);
	// set the time string with current military time
	timeString = uptime.returnHHMMSS(timeinfo->tm_hour,
					 timeinfo->tm_min,
					 timeinfo->tm_sec);	
	// set interval flag
	newInterval = false;
      }    
    else if(elapsedTime >= interval)
      {
	users.clear();
	loadAvgStrings.clear();
	uptimeStrings.clear();
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	// extract end data for CPU line
	extractProcStat(cpuInfoEnd,
			_PROC_STAT);
	// calculate cpu averages
	cpuUsage = calcCPUUsage(cpuInfoStart,
				cpuInfoEnd);

	// store cpu utilization in queue for graph output
	if( cpuUsageVals.empty() ||
	    (cpuUsageVals.size() < (graphMaxCols/_GRAPHBARWIDTH) + 1) )
	  {
	    cpuUsageVals.push(cpuUsage.utilization);
	  }
	else
	  {
	    // deallocate any graph vals larger than our chosen size
	    for(int i = cpuUsageVals.size(); i > ((graphMaxCols/_GRAPHBARWIDTH) + 1); i--)
	      {
		cpuUsageVals.pop();
	      }
	    
	    cpuUsageVals.push(cpuUsage.utilization);
	  }

	double used = memInfo.getMemUsed();
	double avail = memInfo.getMemAvailable();
	double total = memInfo.getMemTotal();
	double usage = 100 - ((avail/total) * 100);
	
	// store current memory utilization
	if( memUsageVals.empty() ||
	    (memUsageVals.size() < (graphMaxCols/_GRAPHBARWIDTH) + 1) )
	  {
	    memUsageVals.push(usage);
	  }
	else
	  {
	    // deallocate any graph vals larger than our chosen size
	    for(int i = memUsageVals.size(); i > ((graphMaxCols/_GRAPHBARWIDTH) + 1); i--)
	      {
		memUsageVals.pop();
	      }
	    
	    memUsageVals.push(usage);
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
	for(std::vector<int>::iterator outer = pidsEnd.begin();
	    outer != pidsEnd.end(); outer++)	
	  {
	    for(std::vector<int>::iterator inner = pidsStart.begin();
		inner != pidsStart.end(); inner++)
	      {
		if(*inner == *outer)		
		  {
		    procInfoEnd.at(*inner)->
		      calcProcCPUUsage(*procInfoStart.at(*outer),
				       *procInfoEnd.at(*inner));
		    procInfoStart.at(*outer)->
		      setCPUUsage(procInfoEnd.at(*inner)->getCPUUsage());
		  }
	      }
	  }

	// count the extracted process states for task window
	// "Tasks: XXX total, X running..."
	countProcessStates(procInfoEnd,
			   taskInfo);
	// set the time string with current military time
	timeString = uptime.returnHHMMSS(timeinfo->tm_hour,
					 timeinfo->tm_min,
					 timeinfo->tm_sec);	
	// set flags and update the new start time for interval
	entered = true;	
	newInterval = true;
	startTime = currentTime;	
      }

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
	    printBadInputString(wins,
				_MAINWIN,
				_YOFFSET - 1,
				0,
				outString);
	    refreshAllWins(wins);
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
	clearAllWins(wins);
      }

    // check for terminal resize and adjust windows accordingly
    updateWinDimensions(wins,
			shiftY,
			shiftX,
			cpuGraphCount,
			memGraphCount);

    // check for cpu graph state
    if( (cpuGraphCount > 0) && (wins.at(_CPUGRAPHWIN)->getWindow() != nullptr) )
      {
	if(cpuGraphCount == 3)
	  {
	    drawGraph(wins,
		      _CPUGRAPHWIN,
		      cpuUsageVals,
		      "CPU UTILIZATION",
		      _GRAPHSCALETWO);
	  }
	else
	  {
	    drawGraph(wins,
		      _CPUGRAPHWIN,
		      cpuUsageVals,
		      "CPU UTILIZATION",
		      _GRAPHSCALEONE);
	  }
      }

    // check for mem graph state
    if( (memGraphCount > 0) && (wins.at(_MEMGRAPHWIN)->getWindow() != nullptr) )
      {
	if(memGraphCount == 3)
	  {
	    drawGraph(wins,
		      _MEMGRAPHWIN,
		      memUsageVals,
		      "MAIN MEMORY USAGE",
		      _GRAPHSCALETWO);
	  }
	else
	  {
	    drawGraph(wins,
		      _MEMGRAPHWIN,
		      memUsageVals,
		      "MAIN MEMORY USAGE",
		      _GRAPHSCALEONE);
	  }
      }

    // print all other top wins
    printTasksWins(wins);
    printCpuWins(wins);
    printMemWins(wins);
    printSwapWins(wins);
    // print top wins data
    attronTopDataWins(wins,
		      A_BOLD);
    printTasksDataWins(wins,
		       taskInfo);
    printCpuDataWins(wins,
		     cpuUsage);
    printMemDataWins(wins,
		     memInfo);
    attroffTopDataWins(wins,
		      A_BOLD);
    // print the color line to the main win
    colorLine = createColorLine(wins.at(_MAINWIN)->getNumCols());
    printLine(wins,
	      _YOFFSET,
	      0,
	      _BLACK_TEXT,
	      _MAINWIN,
	      colorLine);
    defineTopWins(wins,
		  timeString,
		  uptime.getHours()/24,
		  uptime.getHours() % 24,
		  uptime.getMinutes(),
		  loadAvgStrings,
		  numUsers);
    
    // ## update states and print ##
    if(entered == false)
      {
	updateSortState(procInfoStart,
			pidsStart,
			pidsStart,
			sortState);
	updateProgramState(procInfoStart,
			   wins,
			   progState,
			   prevState,
			   sortState,
			   quit,
			   highlight,
			   pidsStart.at(0),
			   shiftY,
			   shiftX,
			   pidsStart.size() - 2,
			   stateChanged,
			   cpuGraphCount,
			   memGraphCount);
	printProcs(wins,
		   procInfoStart,
		   pidsStart,
		   shiftY,
		   shiftX,
		   sortState,
		   highlight);
	colorOnProcWins(wins,
			_BLACK_TEXT);
	printWindowNames(wins,
			 shiftY,
			 shiftX);
	colorOffProcWins(wins,
			 _BLACK_TEXT);
      }
    else if(stateChanged == false)
      {
	updateSortState(procInfoEnd,
			pidsEnd,
			outPids,
			sortState);
	updateProgramState(procInfoEnd,
			   wins,
			   progState,
			   prevState,
			   sortState,
			   quit,
			   highlight,
			   outPids.at(0),
			   shiftY,
			   shiftX,
			   outPids.size() - 2,
			   stateChanged,
			   cpuGraphCount,
			   memGraphCount);
	printProcs(wins,
		   procInfoEnd,
		   outPids,
		   shiftY,
		   shiftX,
		   sortState,
		   highlight);
	colorOnProcWins(wins,
			_BLACK_TEXT);
	printWindowNames(wins,
			 shiftY,
			 shiftX);
	colorOffProcWins(wins,
			 _BLACK_TEXT);
      }
    
    refreshAllWins(wins);
    doupdate();
    usleep(15000);

    for(int i = _TOPWIN; i <= _TOPLOADAVGDATAWIN; i++)
      {
	if(wins.at(i)->getWindow() != nullptr)
	  {
	    wins.at(i)->deleteWindow();
	  }
      }

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

  for(std::unordered_map<int, CursesWindow*>::iterator it
	= wins.begin();
      it != wins.end(); it++)
    {
      it->second->deleteWindow();
    }

  procInfoEnd.clear();
  procInfoStart.clear();
  wins.clear();
        
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
