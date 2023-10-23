/*
  File: 
   main.cpp

  Version: 
   V0.1

  Program Description: 
    A rendition of the Top program using C++. It is currently
    tested in Ubuntu and ArchLinux.  Each have a branch that corresponds to the
    working implementation.  The main branch contains a stable version that works
    on both operating systems.

  Controls:
  - the 'x' key allows highlighting a particular column.
  - the arrow keys allow shifting the windows left and right.
  - the '<' and '>' keys change how the columns are sorted.

  Changes/Fixes Needed:
  - get correct user count
  - determine how Top decides what processes/users have priority in the sort 
    list to come first
  - create a docker image that comes with all the modules necessary for building
    Bottom and GTests.
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
#include "COMMANDWindow.hpp"
#include "cpuWindow.hpp"
#include "cpuInfo.hpp"
#include "cursesColors.hpp"
#include "cursesFunctions.hpp"
#include "cursesWindow.hpp"
#include "extractFileData.hpp"
#include "log.hpp"
#include "mainWindow.hpp"
#include "manageProcesses.hpp"
#include "memInfo.hpp"
#include "memWindow.hpp"
#include "NIWindow.hpp"
#include "percentCPUWindow.hpp"
#include "percentMEMWindow.hpp"
#include "PIDWindow.hpp"
#include "processInfo.hpp"
#include "PRWindow.hpp"
#include "RESWindow.hpp"
#include "secondsToTime.hpp"
#include "SHRWindow.hpp"
#include "sortProcessLists.hpp"
#include "SWindow.hpp"
#include "taskInfo.hpp"
#include "tasksRunningWindow.hpp"
#include "tasksSleepingWindow.hpp"
#include "tasksStoppedWindow.hpp"
#include "tasksTotalWindow.hpp"
#include "tasksZombieWindow.hpp"
#include "tasksWindow.hpp"
#include "TIMEWindow.hpp"
#include "topWindow.hpp"
#include "USERWindow.hpp"
#include "VIRTWindow.hpp"

// debug constants
#define _CURSES 1
#define _LOG 1

// commands and options/modes constants
#define _UTMPDUMP "utmpdump"
#define _READ "r"



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
  CPUInfo cpuInfo;
  TaskInfo taskInfo;
  ProcessInfo* process; // to be populated with all process output data
  std::vector<int> pids; // all currently allocated process PIDs
  std::vector<int> pidsOld; // previously found active PID
  std::vector<int> pidsDead; // PIDs that closed during loop
  std::unordered_map<int, ProcessInfo*> allProcessInfo; // to be populated with /proc/[pid] data

  // window related vars
  std::unordered_map<int, CursesWindow*> allWins;
  MainWindow mainWin;
  TopWindow topWin;
  TasksWindow tasksWin;
  CpuWindow cpuWin;
  MemWindow memWin;
  PIDWindow PIDWin;
  USERWindow USERWin;
  PRWindow PRWin;
  NIWindow NIWin;
  VIRTWindow VIRTWin;
  RESWindow RESWin;
  SHRWindow SHRWin;
  SWindow SWin;
  PercentCPUWindow PercentCPUWin;
  PercentMEMWindow PercentMEMWin;
  TIMEWindow TIMEWin;
  COMMANDWindow COMMANDWin;
  TasksTotalWindow tasksTotalwin;
  TasksRunningWindow tasksRunningWin;
  TasksStoppedWindow tasksStopppedWin;
  TasksSleepingWindow tasksSleepingWin;
  TasksZombieWindow tasksZombieWin;


  // state related vars
  int progState = 0;
  int prevState = 0;
  int sortState = _PROCCPUWIN;
  bool highlight = false;
  bool quit = false;
  int shiftY = 1;
  int shiftX = _PIDWIN;
  std::unordered_map<char, int> progStates;
  
  // ## initialize and setup curses ##
  initializeCurses();
  initializeWindows(allWins,
		    mainWin,
		    topWin,
		    tasksWin,
		    cpuWin,
		    memWin,
		    PIDWin,
		    USERWin,
		    PRWin,
		    NIWin,
		    VIRTWin,
		    RESWin,
		    SHRWin,
		    SWin,
		    PercentCPUWin,
		    PercentMEMWin,
		    TIMEWin,
		    COMMANDWin);

  initializeProgramStates(progStates);

  // loop variables
  SecondsToTime uptime;
  std::vector<std::string> allTopLines;
  std::vector<std::string> parsedLine;
  std::string filePath;
  std::string fileLine;
  std::string tempLine;
  std::string colorLine;
  
  colorLine = createColorLine(allWins.at(_MAINWIN)->getNumCols());
  
  do{
    allTopLines.clear();
    pidsOld = pids;
    pids.clear();
    process = nullptr;

    // get current active PIDS
    pids = findNumericDirs(_PROC);

    // find any processes that died during previous loop
    if(findDeadProcesses(pids, pidsOld, pidsDead))
      {
	// free if any found
	removeDeadProcesses(allProcessInfo, pidsDead);
      }

    // extract data from uptime for very top window
    // "current time, # users, load avg"
    extractProcUptimeLoadavg(uptime,
			     allTopLines);

    // update/add process data for still running and new found processes
    for(int i = 0; i < pids.size(); i++)
      {
	// if new process was found, allocate it
	if(allProcessInfo.count(pids.at(i)) == 0)
	  {
	    process = new ProcessInfo();
	    allProcessInfo.insert(std::make_pair(pids.at(i), process));
	  }

	// extract data for CPU Line
	// "%Cpu(s): x.x us, x.x sy..."
	extractProcStatData(cpuInfo);

	// store line for output
	defineCPULine(cpuInfo,
		      allTopLines);

	// extract data for MiB Mem and MiB swap
	// "MiB Mem: xxxx.xx total, xxxx.xx Free..."
	extractMemInfoData(memInfo);

	// store lines for output
	allTopLines.push_back
	  (setStringMiB(doubleToStr(KiBToMiB(memInfo.getMemTotal()), 1),
			doubleToStr(KiBToMiB(memInfo.getMemFree()), 1),
			doubleToStr(KiBToMiB(memInfo.getMemUsed()), 1),
			doubleToStr(KiBToMiB(memInfo.getBuffCache()), 1)));
	allTopLines.push_back
	  (setStringSwap(doubleToStr(KiBToMiB(memInfo.getSwapTotal()), 1),
			 doubleToStr(KiBToMiB(memInfo.getSwapFree()), 1),
			 doubleToStr(KiBToMiB(memInfo.getSwapUsed()), 1),
			 doubleToStr(KiBToMiB(memInfo.getMemAvailable()), 1)));

	// get pid of current process
	allProcessInfo[pids.at(i)]->setPID(pids.at(i));

	// extract per process data (USER, PR, VIRT...)
	extractProcPidStatus(allProcessInfo,
			     memInfo,
			     uptime,
			     pids.at(i));
	// extract COMMAND
	extractProcComm(allProcessInfo,
			pids.at(i));

	// extract and count process states for task window
	// "Tasks: XXX total, X running..."
	extractProcessStateCount(allProcessInfo,
				 taskInfo);

	// store line for output
	defineTasksLine(taskInfo,
			allTopLines);
      }


    // ## get user input ##
    std::vector<std::pair<double, int>> sortedByDouble;
    std::vector<std::pair<std::string, int>> procStrings;
    std::vector<std::pair<int, int>> sortedByInt;
    std::vector<int> outPids;
    int highlightIndex = 0;
    int userInput = 0;
    int shiftState = 0;
    int previousSortState = sortState;

    shiftState = userInput = getch();
    flushinp();

    // update state values from user input
    updateStateValues(allWins,
		      progStates,
		      userInput,
		      sortState,
		      prevState,
		      progState,
		      highlight,
		      highlightIndex);

    // ## update states ##
    // program state
    changeProgramState(allWins,
		       progState,
		       prevState,
		       quit,
		       highlight);
    
    // change the processes sort state from '<' and '>' user input
    bottomWinsProcSortState(allProcessInfo,
			   pids,
			   outPids,
			   sortState);

    // shift windows up down left or right from arrow key input
    bottomWinsShiftState(allWins,
			shiftState,
			shiftY,
			shiftX,
			outPids.size() - 3);

#if _CURSES
    // ## print process windows ##
    if(highlight == true)
      {
	wattron(allWins.at(highlightIndex)->getWindow(),
		A_BOLD);
      }
    else
      {
	wattroff(allWins.at(highlightIndex)->getWindow(),
		 A_BOLD);
      }

    clearAllWins(allWins);
    printTopWins(allWins,
		 allTopLines);
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
    printColorLine(allWins,
		   _YOFFSET,
		   _BLACK_TEXT,
		   _MAINWIN,
		   colorLine);
    refreshAllWins(allWins);
    doupdate();
    
    if(quit)
      {
	break;
      }
#endif

  } while(true);

#if _CURSES  
  endwin();
#endif
  
  return 0;
} // end of "main"
