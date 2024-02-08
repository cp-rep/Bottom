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
#include "threadWrappers.hpp"

// debug constants
#define _CURSES 1
#define _LOG 1

// commands and options/modes constants
#define _READ "r"

// global vars
std::atomic<bool> isRunning(true);
std::condition_variable cvPrintReadInput;
std::mutex printReadMutex;
bool readFlag = true;
bool printFlag = false;
bool inputFlag = false;



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
		   const std::vector<int>& outPids,
		   int& shiftY,
		   int& shiftX,
		   int& cpuGraphCount,
		   int& memGraphCount,
		   int& sortState,
		   bool& highlight)
{
  std::string colorLine;
  SecondsToTime uptime;

  while(isRunning.load())
    {
      // lock block for printing
      {
	std::unique_lock<std::mutex> lock(printReadMutex);
	cvPrintReadInput.wait(lock, [] { return (printFlag == true && inputFlag == false); });

	// update flags
	readFlag = false;
	printFlag = false;
	inputFlag = false;

	// clear windows and print data
	clearAllWins(wins);
	updateWinDimensions(wins,
			    shiftY,
			    shiftX,
			    cpuGraphCount,
			    memGraphCount);	
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
		   shiftY,
		   shiftX,
		   sortState,
		   highlight);
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
			 shiftY,
			 shiftX);
	colorOffProcWins(wins,
			 _BLACK_TEXT);

	// update flags and notify thread locks
	refreshAllWins(wins);
	doupdate();
	
	readFlag = true;
	inputFlag = true;
	cvPrintReadInput.notify_all();	
      }
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
		    std::vector<int>& outPids,
		    int& progState,
		    int& prevState,
		    int& sortState,
		    bool& highlight,
		    bool& quit,
		    int& shiftY,
		    int& shiftX,
		    int& cpuGraphCount,
		    int& memGraphCount,
		    bool& stateChanged,
		    std::unordered_map<int, CursesWindow*>& wins)
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
  std::string procStatString = _PROC_STAT;
  std::string memString = _PROC_MEMINFO;
  std::string uptimeString = _PROC_UPTIME;
  std::string loadAvgString = _PROC_LOADAVG;  

  while(isRunning.load())
    {
      {
	// lock block for reading
	std::unique_lock<std::mutex> lock(printReadMutex);
	cvPrintReadInput.wait(lock, [] { return (readFlag == true && inputFlag == false);});	
	printFlag = false;
	readFlag = false;
	inputFlag = false;

	// update current time
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	
	// clear necessary old data
	uptimeStrings.clear();
	timeString.clear();
	parsedLoadAvg.clear();
	users.clear();

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

	// extract mutually exclusive data for top wins
	std::thread procThread(extractProcStatThreadWrapper,
			       std::ref(cpuInfoCurr),
			       std::ref(procStatString),
			       &extractProcStat,
			       std::ref(cpuInfoPrev),
			       std::ref(cpuInfoCurr),
			       &calcCPUUsage,
			       std::ref(cpuUsage));
	std::thread memThread(extractProcMeminfo,
			      std::ref(memInfo),
			      std::ref(memString));	
	extractProcUptime(uptime,
			  uptimeStrings,
			  _PROC_UPTIME);
	extractProcLoadavg(parsedLoadAvg,
			   _PROC_LOADAVG);

	// join threads
	procThread.join();
	memThread.join();

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
			sortState);
	updateProgramState(procInfo,
			   wins,
			   progState,
			   prevState,
			   sortState,
			   quit,
			   highlight,
			   outPids.at(0),
			   shiftY,
			   shiftX,
			   outPids.size() + 2,
			   stateChanged,
			   cpuGraphCount,
			   memGraphCount);	

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
	inputFlag = true;
	cvPrintReadInput.notify_all();
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
  std::unordered_map<char, int> progStates;
  bool newInput = false;
  char userInput = '\0';
  DynamicTopWinData dynTWData;
  time_t rawtime;
  struct tm* timeinfo;
  std::vector<std::string> parsedLoadAvg;
  std::string timeString;
  std::vector<int> outPids;
  int progState = 0;
  int prevState = 0;
  int sortState = _PROCCPUWIN;
  bool highlight = false;
  bool quit = false;
  int shiftY = 1;
  int shiftX = _PIDWIN;
  int cpuGraphCount = 0;
  int memGraphCount = 0;
  bool stateChanged = false;
  bool input = false;
  wchar_t c;  

  // init curses and define windows
  initializeCurses();
  initializeStartingWindows(wins);
  defineProcWinsStartVals(wins);
  defineTopWinsStartVals(wins);
  defineTopWinsDataStartVals(wins);
  defineGraphWinStartVals(wins);
  initializeProgramStates(progStates);  
  
  // start threads
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
		       std::ref(outPids),
		       std::ref(progState),
		       std::ref(prevState),
		       std::ref(sortState),
		       std::ref(highlight),
		       std::ref(quit),
		       std::ref(shiftY),
		       std::ref(shiftX),
		       std::ref(cpuGraphCount),
		       std::ref(memGraphCount),
		       std::ref(stateChanged),
		       std::ref(wins));
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
		      std::ref(outPids),
		      std::ref(shiftY),
		      std::ref(shiftX),
		      std::ref(cpuGraphCount),
		      std::ref(memGraphCount),
		      std::ref(sortState),
		      std::ref(highlight));

  while(true)
    {
      std::unique_lock<std::mutex> lock(printReadMutex);
      cvPrintReadInput.wait(lock, [] { return (inputFlag == true); });

      c = getch();
      if(c != -1)
	{
	  if(progStates[c])
	    {
	      prevState = progState;
	      progState = c;
	    }
	}

      flushinp();
      inputFlag = false;
      printReadMutex.unlock();
      cvPrintReadInput.notify_all();
      lock.unlock();

      if(quit == true)
	{
	  isRunning.store(false);
	  break;
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
  
  // join threads
  display.join();
  readData.join();

  // clean up
  endwin();
  
  return 0;
} // end of "main"
