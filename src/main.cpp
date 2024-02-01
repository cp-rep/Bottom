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
/*
#include <algorithm>
#include <atomic>
#include <chrono>
#include <climits>
#include <cmath>
#include <condition_variable>
#include <cstdlib>
#include <ctime>
#include <dirent.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <mutex>
#include <ncurses.h>
#include <pwd.h>
#include <set>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/param.h>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include "_cursesWinConsts.hpp"
#include "_fileConsts.hpp"
#include "_progStateConsts.hpp"
#include "byteConverter.hpp"
#include "COMMANDWindow.hpp"
#include "cpuInfo.hpp"
#include "cpuWindow.hpp"
#include "cursesColors.hpp"
#include "cursesFunctions.hpp"
#include "cursesWindow.hpp"
#include "extractFileData.hpp"
#include "log.hpp"
#include "mainWindow.hpp"
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
#include "sortProcessLists.hpp"
#include "SHRWindow.hpp"
#include "SWindow.hpp"
#include "taskInfo.hpp"
#include "tasksWindow.hpp"
#include "TIMEWindow.hpp"
#include "topWindow.hpp"
#include "USERWindow.hpp"
#include "VIRTWindow.hpp"
*/
// new
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <thread>

// old
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
		   const TaskInfo& taskInfo,
		   const std::vector<int>& pids,
		   std::vector<std::string>& allTopLines)
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
	//	std::vector<int> outPids;
	//	outPids = pids;
	//	std::sort(outPids.begin(), outPids.end());
	//	std::unordered_map<int, ProcessInfo*> test = allProcessInfo;
	//	outPids = sortByCPUUsage(test,
	//				 outPids);
	//	printWindowNames(wins);
	//	printProcs(wins, allProcessInfo, outPids, 0, 0);
	printTasksWins(wins);
	printTasksDataWins(wins,
			   taskInfo);
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
  /*
  initializeProgramStates(progStates);
  */

  // old
  /*
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
  
  initializeWindows(wins,
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


  int sortState = _CPUWIN;
  
  while(true)
    {
      // lock block for printing
      {
	std::unique_lock<std::mutex> lock(printReadMutex);
	dataPrint.wait(lock, [] { return (printFlag == true); });
      
	readFlag = false;
	printFlag = false;
	std::vector<int> outPids;
	outPids = pids;
	std::sort(outPids.begin(), outPids.end());
	std::unordered_map<int, ProcessInfo*> test = allProcessInfo;
	outPids = sortByCPUUsage(test,
				 outPids);
	printTopWins(wins, allTopLines);
	printWindowNames(wins);
	printProcs(wins, allProcessInfo, outPids, 0, 0);
	readFlag = true;
	dataRead.notify_all();
      }
      
      refreshAllWins(wins);
      doupdate();
    }
  */
} // end of "displayThread"



/*
  Function:
   readDataThread
*/
void readDataThread(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
		    TaskInfo& taskInfo,
		    std::vector<int>& pids,
		    std::vector<std::string>& allTopLines)
{
  // new
  MemInfo memInfo;
  CPUInfo cpuInfoStart;
  CPUInfo cpuInfoEnd;
  //  TaskInfo taskInfo;
  //  CPUUsage cpuUsage;
  //  std::vector<int> pidsStartOld;
  //  std::vector<int> pidsEndOld;
  //  std::vector<int> pidsStart;
  //  std::vector<int> pidsEnd;
  //  std::vector<int> pidsStartDead;
  //  std::vector<int> pidsEndDead;
  //  std::set<std::string> users;
  //  int numUsers;
  //  std::unordered_map<int, ProcessInfo*> procInfoStart;
  //  std::unordered_map<int, ProcessInfo*> procInfoEnd;

  // new variables
  std::mutex readDataMutex;
  std::vector<int> pidsOld;
  std::vector<int> pidsDead;
  ProcessInfo* process;
  std::vector<std::string> uptimeStrings;
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

	// clear the output lines for the top windows
	//	allTopLines.clear();

	// store old pids
	pidsOld = pids;
	pids.clear();
	uptimeStrings.clear();
	users.clear();

	// get new pids
	pids = findNumericDirs(_PROC);

	// find any processes that died during main extraction loop
	if(findDeadProcesses(pids, pidsOld, pidsDead))
	  {
	    // free from process list if found
	    removeDeadProcesses(allProcessInfo, pidsDead);
	  }

	extractProcMeminfo(memInfo,
			   _PROC_MEMINFO);

	extractProcUptime(uptime,
			  uptimeStrings,
			  _PROC_UPTIME);
	
	extractProcessData(allProcessInfo,
			   pids,
			   memInfo,
			   uptime,
			   uptimeStrings,
			   users);
	numUsers = users.size();

	countProcessStates(allProcessInfo,
			   taskInfo);

	/*
	// extract data from uptime for very top window
	// "current time, # users, load avg"
	extractProcUptimeLoadavg(uptime,
				 allTopLines);
	*/

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

	    /*
	    // set pid of current process
	    allProcessInfo.at(*it)->setPID(*it);

	    extractProcessData(procInfo,
			       pids,
			       memInfo,
			       uptime,
			       uptimeStrings,
			       users);
	    */
	    /*
	    // extract data for CPU Line "%Cpu(s): x.x. us, 0.5 sy..."
	    extractProcStatData(cpuInfo);

	    // store line for output
	    defineCPULine(cpuInfo, allTopLines);

	    // extract data for MiB Mem and MiB Swap
	    // "MiB Mem: XXXX.XX total, XXXX.XX Free..."
	    extractMemInfoData(memInfo);

	    // store lines for output
	    allTopLines.push_back(setStringMiB(doubleToStr(KiBToMiB(memInfo.getMemTotal()), 1),
					       doubleToStr(KiBToMiB(memInfo.getMemFree()), 1),
					       doubleToStr(KiBToMiB(memInfo.getMemUsed()), 1),
					       doubleToStr(KiBToMiB(memInfo.getBuffCache()), 1)));
	    allTopLines.push_back(setStringSwap(doubleToStr(KiBToMiB(memInfo.getSwapTotal()), 1),
						doubleToStr(KiBToMiB(memInfo.getSwapFree()), 1),
						doubleToStr(KiBToMiB(memInfo.getSwapUsed()), 1),
						doubleToStr(KiBToMiB(memInfo.getMemAvailable()), 1)));

	    // get pid of current process
	    allProcessInfo[pids.at(i)]->setPID(pids.at(i));

	    // extract per process data (USER, PR, VIRT....)
	    extractProcPidStatus(allProcessInfo,
				 memInfo,
				 uptime,
				 pids.at(i));

	    // extract COMMAND
	    extractProcComm(allProcessInfo,
			    pids.at(i));

	    // extract and count process states for task window
	    // "Tasks: XXX total, X running.."
	    extractProcessStateCount(allProcessInfo,
				     taskInfo);

	    // store line for output
	    defineTasksLine(taskInfo,
			    allTopLines);
	    */
	  }
	
	printFlag = true;
	dataPrint.notify_all();
      }
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }



  /*
  // old
  std::mutex readDataMutex;
  std::vector<int> pidsOld;
  std::vector<int> pidsDead;
  SecondsToTime uptime;
  ProcessInfo* process;
  MemInfo memInfo;
  CPUInfo cpuInfo;
  TaskInfo taskInfo;
  std::vector<std::string> parsedLine;
  std::string tempLine;
  std::string fileLine;
  std::string filePath;
  std::string lineString;
  time_t rawtime;
  struct tm* timeinfo;
  
  while(true)
    {
      // lock block for reading
      {
	std::unique_lock<std::mutex> lock(printReadMutex);
	dataRead.wait(lock, [] { return ( readFlag == true ); });
	printFlag = false;
	readFlag = false;

	// clear the output lines for the top windows
	allTopLines.clear();

	// store old pids
	pidsOld = pids;
	pids.clear();

	// get new pids
	pids = findNumericDirs(_PROC);

	// find any processes that died during main extraction loop
	if(findDeadProcesses(pids, pidsOld, pidsDead))
	  {
	    // free from process list if found
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

	    // extract data for CPU Line "%Cpu(s): x.x. us, 0.5 sy..."
	    extractProcStatData(cpuInfo);

	    // store line for output
	    defineCPULine(cpuInfo, allTopLines);

	    // extract data for MiB Mem and MiB Swap
	    // "MiB Mem: XXXX.XX total, XXXX.XX Free..."
	    extractMemInfoData(memInfo);

	    // store lines for output
	    allTopLines.push_back(setStringMiB(doubleToStr(KiBToMiB(memInfo.getMemTotal()), 1),
					       doubleToStr(KiBToMiB(memInfo.getMemFree()), 1),
					       doubleToStr(KiBToMiB(memInfo.getMemUsed()), 1),
					       doubleToStr(KiBToMiB(memInfo.getBuffCache()), 1)));
	    allTopLines.push_back(setStringSwap(doubleToStr(KiBToMiB(memInfo.getSwapTotal()), 1),
						doubleToStr(KiBToMiB(memInfo.getSwapFree()), 1),
						doubleToStr(KiBToMiB(memInfo.getSwapUsed()), 1),
						doubleToStr(KiBToMiB(memInfo.getMemAvailable()), 1)));

	    // get pid of current process
	    allProcessInfo[pids.at(i)]->setPID(pids.at(i));

	    // extract per process data (USER, PR, VIRT....)
	    extractProcPidStatus(allProcessInfo,
				 memInfo,
				 uptime,
				 pids.at(i));

	    // extract COMMAND
	    extractProcComm(allProcessInfo,
			    pids.at(i));

	    // extract and count process states for task window
	    // "Tasks: XXX total, X running.."
	    extractProcessStateCount(allProcessInfo,
				     taskInfo);

	    // store line for output
	    defineTasksLine(taskInfo,
			    allTopLines);
	  }
	
	printFlag = true;
	dataPrint.notify_all();
      }

      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

  // cleanup allocated processes before joining
  for(std::unordered_map<int, ProcessInfo*>::iterator it = allProcessInfo.begin();
      it != allProcessInfo.end(); it++)
    {
      delete(it->second);
    }
  
  allProcessInfo.clear();
  */
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
  std::vector<int> pids;
  std::unordered_map<int, int> progStates;
  std::vector<std::string> allTopLines;
  bool newInput = false;
  char userInput = '\0';

  /*
    std::condition_variable dataPrint;
    std::condition_variable dataRead;
    std::mutex printReadMutex;
    bool readFlag = true;
    bool printFlag = false;
  */
  
  std::thread input(inputThread,
		    std::ref(userInput),
		    std::ref(newInput));
  std::thread readData(readDataThread,
		       std::ref(allProcessInfo),
		       std::ref(taskInfo),
		       std::ref(pids),
		       std::ref(allTopLines));
  std::thread display(displayThread,
		      std::ref(userInput),
		      std::ref(newInput),
		      std::ref(wins),
		      std::ref(allProcessInfo),
		      std::ref(taskInfo),
		      std::ref(pids),
		      std::ref(allTopLines));		      
    
  input.join();
  display.join();
  readData.join();
  endwin();
  
  return 0;
} // end of "main"



/*
  Function:
   printWindowToLog

  Description:
   A debugging function that prints a CursesWindow object's current data members
   to the log file.

  Input:
  log             - a reference to an output file stream object, the
                    log file in the /Bottom/log/ folder
		    
  win             - A const reference to a CursesWindow object that will
                    be used to print it's member data to the log file.

  Output:
  None
*/
void printWindowToLog(std::ofstream& log, const CursesWindow& win)
{
  log << "m_windowName: " << win.getWindowName() << std::endl;
  log << "m_numLines: " << win.getNumLines() << std::endl;
  log << "m_numCols: " << win.getNumCols() << std::endl;
  log << "m_startY: " << win.getStartY() << std::endl;
  log << "m_startX: " << win.getStartX() << std::endl;
} // end of "printWindowToLog"
