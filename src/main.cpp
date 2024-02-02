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
  - get/calculate TIME+ window
  - determine how Top decides what processes/users have priority in the sort 
    list to come first
  - create a docker image that comes with all the modules necessary for building
    Bottom and GTests for easier/"safer" testing for interested parties.
*/
#include <algorithm>
#include <atomic>
#include <chrono>
#include <climits>
#include <cmath>
#include <condition_variable>
#include <ctime>
#include <dirent.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <mutex>
#include <ncurses.h>
#include <pwd.h>
#include <queue>
#include <unordered_map>
#include <unistd.h>
#include <set>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/param.h>
#include <thread>
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

// commands and options/modes constants
#define _UTMPDUMP "utmpdump"
#define _READ "r"

// function prototypes
void printWindowToLog(std::ofstream& log,
		      const CursesWindow& win);
const std::vector<int> sortByUSER
(const std::vector<int>& pidNums,
 std::unordered_map<int, ProcessInfo*>& procData);
std::condition_variable dataPrint;
std::condition_variable dataRead;
std::mutex printReadMutex;
bool readFlag = true;
bool printFlag = false;



/*
  Function:
  inputThread
*/
void inputThread(char& userInput,
		 bool& newInput)
{
} // end of "inputThread"



/*
  Function:
  displayThread
*/
void displayThread(char& userInput,
		   bool& newInput,
		   std::unordered_map<int, CursesWindow*>& wins,
		   const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
		   const CPUUsage& cpuUsage,
		   const MemInfo& memInfo,
		   const TaskInfo& taskInfo,
		   const std::vector<int>& pids)
{
  std::string colorLine;

  initializeCurses();
  initializeStartingWindows(wins);
  defineProcWinsStartVals(wins);
  defineTopWinsStartVals(wins);
  defineTopWinsDataStartVals(wins);
  defineGraphWinStartVals(wins);

  while(true)
    {
      // lock block for printing
      {
	std::unique_lock<std::mutex> lock(printReadMutex);
	dataPrint.wait(lock, [] { return (printFlag == true); });
      
	readFlag = false;
	printFlag = false;
	printTasksWins(wins);
	printCpuWins(wins);
	printMemWins(wins);
	printSwapWins(wins);
	printTasksDataWins(wins,
			   taskInfo);
	printCpuDataWins(wins,
			 cpuUsage);
	printMemDataWins(wins,
			 memInfo);
	printProcs(wins,
		   allProcessInfo,
		   pids,
		   0,
		   0,
		   0,
		   0);
	colorLine = createColorLine(wins.at(_MAINWIN)->getNumCols());
	printLine(wins,
		  _YOFFSET,
		  0,
		  _BLACK_TEXT,
		  _MAINWIN,
		  colorLine);	
	colorOnProcWins(wins,
			_BLACK_TEXT);
	printWindowNames(wins,
			 0,
			 0);
	colorOffProcWins(wins,
			 _BLACK_TEXT);
	
	readFlag = true;
	dataRead.notify_all();
      }
      
      refreshAllWins(wins);
      doupdate();
    }
} // end of "displayThread"



/*
  Function:
   readDataThread
*/
void readDataThread(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
		    CPUUsage& cpuUsage,
		    MemInfo& memInfo,
		    TaskInfo& taskInfo,
		    std::vector<int>& pids)
{
  // new variables
  CPUInfo cpuInfo;
  std::mutex readDataMutex;
  std::vector<int> pidsOld;
  std::vector<int> pidsDead;
  ProcessInfo* process;
  std::vector<std::string> uptimeStrings;
  std::vector<std::string> loadAvgStrings;
  SecondsToTime uptime;
  int numUsers;
  std::set<std::string> users;

  while(true)
    {
      // lock block for reading
      {
	std::unique_lock<std::mutex> lock(printReadMutex);
	dataRead.wait(lock, [] { return ( readFlag == true ); });
	printFlag = false;
	readFlag = false;

	// store old pids
	pidsOld = pids;
	pids.clear();
	uptimeStrings.clear();
	loadAvgStrings.clear();
	users.clear();

	// get new pids
	pids = findNumericDirs(_PROC);

	// find any processes that died during main extraction loop
	if(findDeadProcesses(pids, pidsOld, pidsDead))
	  {
	    // free from process list if found
	    removeDeadProcesses(allProcessInfo, pidsDead);
	  }
	
	extractProcStat(cpuInfo,
			_PROC_STAT);

	// this needs to be fixed for interval
	cpuUsage = calcCPUUsage(cpuInfo,
				cpuInfo);
	extractProcMeminfo(memInfo,
			   _PROC_MEMINFO);
	extractProcUptime(uptime,
			  uptimeStrings,
			  _PROC_UPTIME);
	extractProcLoadavg(loadAvgStrings,
			   _PROC_LOADAVG);
	extractProcessData(allProcessInfo,
			   pids,
			   memInfo,
			   uptime,
			   uptimeStrings,
			   users);
	numUsers = users.size();
	countProcessStates(allProcessInfo,
			   taskInfo);

	// update/add process data for still running and new found processes
	for(int i = 0; i < pids.size(); i++)
	  {
	    for(std::vector<int>::const_iterator it = pids.begin(); it != pids.end(); it++)
	      {
		// if new process was found, allocate it
		if(allProcessInfo.count(*it) == 0)
		  {
		    process = new ProcessInfo();
		    allProcessInfo.insert(std::make_pair(*it, process));
		  }
		allProcessInfo.at(*it)->setPID(*it);
	      }
	  }
	
	printFlag = true;
	dataPrint.notify_all();
      }
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
} // end of "readDataThread"



/*
  Function:
   main

  Description:
   The main driver function for the Bottom program.
*/
int main()
{
  std::unordered_map<int, CursesWindow*> wins;
  std::unordered_map<int, ProcessInfo*> allProcessInfo;
  TaskInfo taskInfo;
  CPUUsage cpuUsage;
  MemInfo memInfo;
  std::vector<int> pids;
  std::unordered_map<int, int> progStates;
  bool newInput = false;
  char userInput = '\0';
  
  std::thread input(inputThread,
		    std::ref(userInput),
		    std::ref(newInput));
  std::thread readData(readDataThread,
		       std::ref(allProcessInfo),
		       std::ref(cpuUsage),
		       std::ref(memInfo),
		       std::ref(taskInfo),
		       std::ref(pids));
  std::thread display(displayThread,
		      std::ref(userInput),
		      std::ref(newInput),
		      std::ref(wins),
		      std::ref(allProcessInfo),
		      std::ref(cpuUsage),
		      std::ref(memInfo),
		      std::ref(taskInfo),
		      std::ref(pids));
    
  input.join();
  display.join();
  readData.join();
  endwin();
  
  return 0;
} // end of "main"
