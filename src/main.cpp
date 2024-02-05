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
#include "dynData.hpp"
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

// global vars
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

  /*
  while(true);
  std::this_thread::sleep_for(std::chrono::nanoseconds(500));
  */
} // end of "inputThread"



/*
  Function:
  displayThread
*/
void displayThread(char& userInput,
		   bool& newInput,
		   std::unordered_map<int, CursesWindow*>& wins,
		   const std::unordered_map<int, ProcessInfo*>& procInfo,
		   const CPUUsage& cpuUsage,
		   const MemInfo& memInfo,
		   const TaskInfo& taskInfo,
		   const std::vector<int>& pids,
		   const struct DynamicTopWinData& dynTWData,
		   const std::vector<std::string>& parsedLoadAvg,
		   const std::string& timeString,
		   const std::vector<int>& outPids)
{
  std::string colorLine;
  SecondsToTime uptime;

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
	clearAllWins(wins);
	printTopWins(wins,
		     dynTWData,
		     parsedLoadAvg,
		     timeString);
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
		   procInfo,
		   outPids,
		   1,
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

	// update flags and notify thread locks
	readFlag = true;
	dataRead.notify_all();
      }

      refreshAllWins(wins);
      doupdate();

      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
} // end of "displayThread"



/*
  Function:
   readDataThread
*/
void readDataThread(std::unordered_map<int, ProcessInfo*>& procInfo,
		    CPUUsage& cpuUsage,
		    MemInfo& memInfo,
		    TaskInfo& taskInfo,
		    std::vector<int>& pids,
		    struct DynamicTopWinData& dynTWData,
		    time_t rawtime,
		    struct tm* timeinfo,
		    std::vector<std::string>& parsedLoadAvg,
		    std::string& timeString,
		    std::vector<int>& outPids)
{
  // new variables
  CPUInfo cpuInfoCurr;
  CPUInfo cpuInfoPrev;
  std::mutex readDataMutex;
  std::vector<int> pidsOld;
  std::vector<int> pidsDead;
  ProcessInfo* process;
  std::vector<std::string> uptimeStrings;
  SecondsToTime uptime;
  int numUsers;
  std::set<std::string> users;
  std::unordered_map<int, ProcessInfo*> procInfoPrev;
  std::chrono::high_resolution_clock::time_point prevTime;
  std::chrono::high_resolution_clock::time_point currTime;

  while(true)
    {
      {
	// lock block for reading
	std::unique_lock<std::mutex> lock(printReadMutex);
	dataRead.wait(lock, [] { return ( readFlag == true ); });
	printFlag = false;
	readFlag = false;

	// clear necessary old data
	uptimeStrings.clear();
	timeString.clear();
	parsedLoadAvg.clear();
	users.clear();

	// update current time
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	// get new pids
	pidsOld.clear();
	pidsOld = pids;
	pids.clear();
	pidsDead.clear();
	pids = findNumericDirs(_PROC);
	cpuInfoPrev = cpuInfoCurr;
	prevTime = currTime;

	// copy old processes
	for(std::vector<int>::const_iterator it = pidsOld.begin(); it != pidsOld.end(); it++)
	  {
	    process = new ProcessInfo(*procInfo.at(*it));
	    procInfoPrev.insert(std::make_pair(*it, process));
	  }
	
	// extract process and system data
	extractProcStat(cpuInfoCurr,
			_PROC_STAT);
	cpuUsage = calcCPUUsage(cpuInfoPrev,
				cpuInfoCurr);
	extractProcMeminfo(memInfo,
			   _PROC_MEMINFO);
	extractProcUptime(uptime,
			  uptimeStrings,
			  _PROC_UPTIME);
	extractProcLoadavg(parsedLoadAvg,
			   _PROC_LOADAVG);

	if(parsedLoadAvg.empty())
	  {
	    endwin();
	    exit(EXIT_FAILURE);
	  }

	// find any processes that died during main extraction loop
	if(findDeadProcesses(pids, pidsOld, pidsDead))
	  {
	    // free from process list if found
	    removeDeadProcesses(procInfo, pidsDead);
	  }
	
	extractProcessData(procInfo,
			   pids,
			   memInfo,
			   uptime,
			   uptimeStrings,
			   users);
	numUsers = users.size();
	countProcessStates(procInfo,
			   taskInfo);
	timeString = uptime.returnHHMMSS(timeinfo->tm_hour,
					 timeinfo->tm_min,
					 timeinfo->tm_sec);
	extractSysInfo(uptime.getHours() / 24,
		       uptime.getHours() % 24,
		       uptime.getMinutes(),
		       parsedLoadAvg,
		       numUsers,
		       dynTWData);

	// update/add process data for still running and new found processes
	for(int i = 0; i < pids.size(); i++)
	  {
	    for(std::vector<int>::const_iterator it = pids.begin(); it != pids.end(); it++)
	      {
		// if new process was found, allocate it
		if(procInfo.count(*it) == 0)
		  {
		    process = new ProcessInfo();
		    procInfo.insert(std::make_pair(*it, process));
		  }
		procInfo.at(*it)->setPID(*it);
	      }
	  }

	// calculate the passed time
	unsigned long elapsedTicks;
	currTime = std::chrono::high_resolution_clock::now();	
	elapsedTicks = std::chrono::duration_cast<std::chrono::seconds>(currTime - prevTime).count()
	* sysconf(_SC_CLK_TCK);

	// calculate per process cpu usage
	for(std::vector<int>::iterator outer = pids.begin();
	    outer != pids.end(); outer++)
	  {
	    for(std::vector<int>::iterator inner = pidsOld.begin();
		inner != pidsOld.end(); inner++)
	      {
		if(*inner == *outer)
		  {
		    procInfo.at(*inner)->
		      calcProcCPUUsage(*procInfoPrev.at(*outer),
				       *procInfo.at(*outer),
				       elapsedTicks);
		  }
	      }
	  }

	// update sort states
	updateSortState(procInfo,
			pids,
			outPids,
			_PROCCPUWIN);

	// clean up the previously allocated processes
	for(std::unordered_map<int, ProcessInfo*>::iterator it
	      = procInfoPrev.begin();
	    it != procInfoPrev.end(); it++)
	  {
	    delete(it->second);
	    it->second = nullptr;
	  }
	
	procInfoPrev.clear();

	// notify threads
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
  std::unordered_map<int, ProcessInfo*> procInfo;
  TaskInfo taskInfo;
  CPUUsage cpuUsage;
  MemInfo memInfo;
  std::vector<int> pids;
  std::unordered_map<int, int> progStates;
  bool newInput = false;
  char userInput = '\0';
  DynamicTopWinData dynTWData;
  time_t rawtime;
  struct tm* timeinfo;
  std::vector<std::string> parsedLoadAvg;
  std::string timeString;
  std::vector<int> outPids;

  // start threads
  std::thread input(inputThread,
		    std::ref(userInput),
		    std::ref(newInput));
  std::thread readData(readDataThread,
		       std::ref(procInfo),
		       std::ref(cpuUsage),
		       std::ref(memInfo),
		       std::ref(taskInfo),
		       std::ref(pids),
		       std::ref(dynTWData),
		       std::ref(rawtime),
		       std::ref(timeinfo),
		       std::ref(parsedLoadAvg),
		       std::ref(timeString),
		       std::ref(outPids));
  std::thread display(displayThread,
		      std::ref(userInput),
		      std::ref(newInput),
		      std::ref(wins),
		      std::ref(procInfo),
		      std::ref(cpuUsage),
		      std::ref(memInfo),
		      std::ref(taskInfo),
		      std::ref(pids),
		      std::ref(dynTWData),
		      std::ref(parsedLoadAvg),
		      std::ref(timeString),
		      std::ref(outPids));

  // join threads
  //  input.join();
  display.join();
  readData.join();

  // clean up
  endwin();
  
  return 0;
} // end of "main"
