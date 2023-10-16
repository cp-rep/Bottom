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

  Changes Needed:
  - get correct user count
  - get/calculate TIME+ window
  - fix %CPU value calculations
  - get/calculate %MEM value
  - determine how Top decides what processes/users have priority in the sort 
    list to come first
  - remove SecondsToTime class and put related functions in a new file called
    calculateTime.hpp/cpp
  - create a docker image that comes with all the modules necessary for building
    Bottom and GTests for easier/safe testing for interested parties.
  - Find why Top's %CPU calculation updates faster for processes that are
    allocated after Bottom is already running
  - add function that takes a vector parameter that determines which lines are
    desired for output on the Top Windows
  - fix the printing order so that the smear no longer occurs
*/
#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <curses.h>
#include <climits>
#include <limits>
#include <iomanip>
#include <unistd.h>
#include <unordered_map>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/param.h>
#include <pwd.h>
#include <dirent.h>
#include <algorithm>
#include <set>
#include "log.hpp"
#include "cursesWindow.hpp"
#include "mainWindow.hpp"
#include "topWindow.hpp"
#include "tasksWindow.hpp"
#include "VIRTWindow.hpp"
#include "COMMANDWindow.hpp"
#include "cpuWindow.hpp"
#include "cpuInfo.hpp"
#include "memWindow.hpp"
#include "NIWindow.hpp"
#include "percentCPUWindow.hpp"
#include "percentMEMWindow.hpp"
#include "PIDWindow.hpp"
#include "PRWindow.hpp"
#include "RESWindow.hpp"
#include "SHRWindow.hpp"
#include "SWindow.hpp"
#include "TIMEWindow.hpp"
#include "USERWindow.hpp"
#include "extractFileData.hpp"
#include "byteConverter.hpp"
#include "memInfo.hpp"
#include "processInfo.hpp"
#include "secondsToTime.hpp"
#include "cursesFunctions.hpp"
#include "cursesColors.hpp"
#include "_progStateConsts.hpp"
#include "_cursesWinConsts.hpp"
#include "_fileConsts.hpp"
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
  ProcessInfo* processInfo;
  std::vector<int> pidNums; // to be populated with all current /proc/[pid] numbers
  std::unordered_map<int, ProcessInfo*> procData; // to be populated with /proc/[pid] data
  std::unordered_map<int, ProcessInfo*>::iterator procDataIt;

  // window related vars
  std::unordered_map<int, CursesWindow*> allWins;
  short numLines = 0;
  short numCols = 0;
  short startY = 0;
  short startX = 0;

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
#if _CURSES  
  MainWindow mainWin(initscr(),
		     "Main",
		     0,
		     0,
		     0,
		     0);
  getmaxyx(mainWin.getWindow(), numLines, numCols);
  mainWin.setNumLines(numLines);
  mainWin.setNumCols(numCols);
  mainWin.setStartX(0);
  mainWin.setStartY(0);
  
  if(has_colors())
    {
      start_color();
      init_pair(_WHITE_TEXT, COLOR_WHITE, COLOR_BLACK);
      init_pair(_BLACK_TEXT, COLOR_BLACK, COLOR_WHITE);
    }

  noecho();
  cbreak();
  curs_set(false);
  keypad(mainWin.getWindow(), true);
  nodelay(mainWin.getWindow(), true);

  // ## define windows ##
  // define topWindow
  numLines = 1;
  numCols = numCols;
  startY = _YOFFSET - 6;
  startX = 0;
  TopWindow topWin(newwin(numLines,
			  numCols,
			  startY,
			  startX),
		   "top",
		   numLines,
		   numCols,
		   startY,
		   startX);
  topWin.getTopLine();
  // define tasks window
  numLines = 1;
  numCols = numCols;
  startY = _YOFFSET - 5;
  startX = 0;
  TasksWindow tasksWin(newwin(numLines,
			      numCols,
			      startY,
			      startX),
		       "Tasks",
		       numLines,
		       numCols,
		       startY,
		       startX);
  // define cpu window
  numLines = 1;
  numCols = numCols;
  startY = _YOFFSET - 4;
  startX = 0;
  CpuWindow cpuWin(newwin(numLines,
			  numCols,
			  startY,
			  startX),
		   "CPU",
		   numLines,
		   numCols,
		   startY,
		   startX);
  // define mem window
  numLines = 2;
  numCols = numCols;
  startY = _YOFFSET - 3;
  startX = 0;  
  MemWindow memWin(newwin(numLines,
			  numCols,
			  startY,
			  startX),
		   "MEM",
		   numLines,
		   numCols,
		   startY,
		   startX);
  // define PID window
  numLines = mainWin.getNumLines() -
    memWin.getNumLines() -
    cpuWin.getNumLines() -
    tasksWin.getNumLines() -
    topWin.getNumLines() - 1;
  numCols = 7;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = 0;
  PIDWindow PIDWin(newwin(numLines,
			  numCols,
			  startY,
			  startX),
		   "PID",
		   numLines,
		   numCols,
		   startY,
		   startX);
  // define USER window
  numCols = 8;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() + 1;
  USERWindow USERWin(newwin(numLines,
			    numCols,
			    startY,
			    startX),
		     "USER",
		     numLines,
		     numCols,
		     startY,
		     startX);
  // define PR window
  numCols = 3;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() + 2;
  PRWindow PRWin(newwin(numLines,
			numCols,
			startY,
			startX),
		 "PR",
		 numLines,
		 numCols,
		 startY,
		 startX);
  // define NI window
  numCols = 3;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() + 3;
  NIWindow NIWin(newwin(numLines,
			numCols,
			startY,
			startX),
		 "NI",
		 numLines,
		 numCols,
		 startY,
		 startX);
  // define VIRT window
  numCols = 7;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() +
    NIWin.getNumCols() + 4;
  VIRTWindow VIRTWin(newwin(numLines,
			    numCols,
			    startY,
			    startX),
		     "VIRT",
		     numLines,
		     numCols,
		     startY,
		     startX);
  // define RES window
  numCols = 6;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() +
    NIWin.getNumCols() +
    VIRTWin.getNumCols() + 5;
  RESWindow RESWin(newwin(numLines,
			  numCols,
			  startY,
			  startX),
		   "RES",
		   numLines,
		   numCols,
		   startY,
		   startX);
  // define SHR window
  numCols = 6;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() +
    NIWin.getNumCols() +
    VIRTWin.getNumCols() +
    RESWin.getNumCols() + 6;
  SHRWindow SHRWin(newwin(numLines,
			  numCols,
			  startY,
			  startX),
		   "SHR",
		   numLines,
		   numCols,
		   startY,
		   startX);
  // define S window
  numCols = 1;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() +
    NIWin.getNumCols() +
    VIRTWin.getNumCols() +
    RESWin.getNumCols() +
    SHRWin.getNumCols() + 7;
  SWindow SWin(newwin(numLines,
		      numCols,
		      startY,
		      startX),
	       "S",
	       numLines,
	       numCols,
	       startY,
	       startX);
  // define PercentCPU window
  numCols = 5;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() +
    NIWin.getNumCols() +
    VIRTWin.getNumCols() +
    RESWin.getNumCols() +
    SHRWin.getNumCols() + 
    SWin.getNumCols() + 8;
  PercentCPUWindow PercentCPUWin(newwin(numLines,
				  numCols,
				  startY,
				  startX),
				 "%CPU",
				 numLines,
				 numCols,
				 startY,
				 startX);
  // define PercentMEM window
  numCols = 5;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() +
    NIWin.getNumCols() +
    VIRTWin.getNumCols() +
    RESWin.getNumCols() +
    SHRWin.getNumCols() + 
    SWin.getNumCols() +
    PercentCPUWin.getNumCols() + 9;
  PercentMEMWindow PercentMEMWin(newwin(numLines,
				  numCols,
				  startY,
				  startX),
				 "%MEM",
				 numLines,
				 numCols,
				 startY,
				 startX);
  // define TIME window
  numCols = 9;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() +
    NIWin.getNumCols() +
    VIRTWin.getNumCols() +
    RESWin.getNumCols() +
    SHRWin.getNumCols() + 
    SWin.getNumCols() +
    PercentCPUWin.getNumCols() + 
    PercentMEMWin.getNumCols() + 10;  
  TIMEWindow TIMEWin(newwin(numLines,
			    numCols,
			    startY,
			    startX),
		     "TIME+",
		     numLines,
		     numCols,
		     startY,
		     startX);
  // define COMMAND window
  numCols = 48;
  startY = memWin.getStartY() + _YOFFSET - 3;
  startX = PIDWin.getNumCols() +
    USERWin.getNumCols() +
    PRWin.getNumCols() +
    NIWin.getNumCols() +
    VIRTWin.getNumCols() +
    RESWin.getNumCols() +
    SHRWin.getNumCols() + 
    SWin.getNumCols() +
    PercentCPUWin.getNumCols() + 
    PercentMEMWin.getNumCols() +
    TIMEWin.getNumCols() + 11;
  COMMANDWindow COMMANDWin(newwin(numLines,
				  numCols,
				  startY,
				  startX), 
			   "COMMAND",
			   numLines,
			   numCols,
			   startY,
			   startX);
  
  // ## store all startup windows ##
  allWins.insert(std::make_pair(_MAINWIN,&mainWin));
  allWins.insert(std::make_pair(_TOPWIN, &topWin));
  allWins.insert(std::make_pair(_TASKSWIN, &tasksWin));
  allWins.insert(std::make_pair(_CPUWIN, &cpuWin));
  allWins.insert(std::make_pair(_MEMWIN, &memWin));
  allWins.insert(std::make_pair(_PIDWIN, &PIDWin));
  allWins.insert(std::make_pair(_USERWIN, &USERWin));
  allWins.insert(std::make_pair(_PRWIN, &PRWin));
  allWins.insert(std::make_pair(_NIWIN, &NIWin));
  allWins.insert(std::make_pair(_VIRTWIN, &VIRTWin));
  allWins.insert(std::make_pair(_RESWIN, &RESWin));
  allWins.insert(std::make_pair(_SHRWIN, &SHRWin));
  allWins.insert(std::make_pair(_SWIN, &SWin));
  allWins.insert(std::make_pair(_PROCCPUWIN, &PercentCPUWin));
  allWins.insert(std::make_pair(_PROCMEMWIN, &PercentMEMWin));
  allWins.insert(std::make_pair(_PROCTIMEWIN, &TIMEWin));
  allWins.insert(std::make_pair(_COMMANDWIN, &COMMANDWin));

  // ## create colorLine ##
  std::string colorLine;
  colorLine = createColorLine(mainWin.getNumCols());

  // ## define program states ##
  progStates.insert(std::make_pair(_PROGSTATEHELP, 1)); // open help menu
  progStates.insert(std::make_pair(_PROGSTATEQUIT, 1)); // quit
  progStates.insert(std::make_pair(_PROGSTATEHL, 1)); // highlight column
#endif

  // ## run the main program loop ##
  do{
    std::vector<std::string> parsedLine;
    std::vector <std::string> outLines;
    std::string tempLine;
    std::string fileLine;
    int val = 0;

    // get topWin data
    fileLine = returnFileLineByNumber(_UPTIME, 1);
    parsedLine = parseLine(fileLine);
    val = convertToInt(parsedLine.at(0));
    SecondsToTime uptime(val);
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    tempLine = uptime.returnHHMMSS(timeinfo->tm_hour,
				   timeinfo->tm_min,
				   timeinfo->tm_sec);
    fileLine = returnFileLineByNumber("/proc/loadavg", 1);
    parsedLine = parseLine(fileLine);
#if _CURSES    
    topWin.defineTopLine(tempLine,
			 uptime.getHours()/24,
			 uptime.getHours() % 24,
			 uptime.getMinutes(),
			 parsedLine);
    outLines.push_back(topWin.getTopLine());    
#endif    
    
    tempLine.clear();
    // ## find running processes and update the list if needed ##
    // store old process list
    std::vector<int> pidNumsOld(pidNums);
    std::vector<int> pidNumsDead;

    // get new process list
    pidNums.clear();
    pidNums = findNumericDirs(_PROC);
    std::sort(pidNums.begin(), pidNums.end());
    
    // find any dead processes
    for(int i = 0; i < pidNumsOld.size(); i++)
      {
	bool exists = false;
	
	for(int j = 0; j < pidNums.size(); j++)
	  {
	    if(pidNumsOld.at(i) == pidNums.at(j))
	      {
		exists = true;
		break;
	      }
	  }

	if(exists == false)
	  {
	    pidNumsDead.push_back(pidNumsOld.at(i));
	  }
      }

    // remove dead processes from the process umap
    for(int i = 0; i < pidNumsDead.size(); i++)
      {
	if(procData.count(pidNumsDead.at(i)) > 0)
	  {
	    delete(procData[pidNumsDead.at(i)]);
	    procData.erase(pidNumsDead.at(i));
	  }
      }

    // update processes data
    for(int i = 0; i < pidNums.size(); i++)
      {
	// if process is new, allocate it
	if(procData.count(pidNums.at(i)) == 0)
	  {
	    processInfo = new ProcessInfo();
	    procData.insert(std::make_pair(pidNums.at(i), processInfo));
	  }
	    std::string filePath;
	    std::string lineString;
	    const std::string currProc = _PROC + std::to_string(pidNums.at(i));
	    unsigned int value = 0;

	    // set pid
	    procData[pidNums.at(i)]->setPID(pidNums.at(i));

	    // get command
	    filePath = currProc;
	    filePath.append(_COMM);
	    lineString = returnFileLineByNumber(filePath, 1);
	    procData[pidNums.at(i)]->setCOMMAND(lineString);

 	    // get USER
	    filePath = currProc;
	    filePath.append(_STATUS);
	    lineString = returnPhraseLine(filePath, "Gid");

	    if(lineString != "-1")
	      {
		struct passwd userData;
		struct passwd* userDataPtr;
		uid_t uidt;
		char buff[1024];		
		
		parsedLine = parseLine(lineString);
		uidt = convertToInt(parsedLine.at(1));
		
		if(getpwuid_r(uidt, &userData, buff, sizeof(buff), &userDataPtr))
		  {
#if _LOG		    
		    log << "Failed to call getpwuid_r()" << std::endl;
#endif		    
		  }
		else
		  {
		    procData[pidNums.at(i)]->setUSER(userData.pw_name);		    
		  }
	      }
	    else
	      {
		procData[pidNums.at(i)]->setUSER("-1");
	      }

	    // get VIRT
	    lineString = returnFileLineByPhrase(filePath, "VmSize");
	    if(lineString != "-1")
	      {
		parsedLine = parseLine(lineString);
		value = convertToInt(parsedLine.at(1));
		procData[pidNums.at(i)]->setVIRT(value);
	      }

	    // get RES
	    lineString = returnFileLineByPhrase(filePath, "VmRSS");
	    if(lineString != "-1")
	      {
		parsedLine = parseLine(lineString);
		value = convertToInt(parsedLine.at(1));
		procData[pidNums.at(i)]->setRes(value);
	      }

	    // get SHR
	    lineString = returnFileLineByPhrase(filePath, "RssFile");
	    if(lineString != "-1")
	      {
		parsedLine = parseLine(lineString);
		value = convertToInt(parsedLine.at(1));
		procData[pidNums.at(i)]->setSHR(value);
	      }

 	    // get PR
	    filePath = currProc;
	    filePath.append(_STAT);
	    lineString = returnFileLineByNumber(filePath, 1);

	    if(lineString != "-1")
	      {
		double utime = 0;
		double cutime = 0;
		double pstart = 0;
		double newVal = 0;
		int intPercentage = 0;
		
		// get uptime
		fileLine = returnFileLineByNumber(_UPTIME, 1);
		parsedLine = parseLine(fileLine);
		newVal = stringToDouble(parsedLine.at(0));
		uptime.setTotalSecs(newVal);
		procData[pidNums.at(i)]->setCPUUsage(newVal);

		// get priority
		lineString = fixStatLine(lineString);
		parsedLine = parseLine(lineString);
		value = convertToInt(parsedLine.at(15));
		procData[pidNums.at(i)]->setPR(value);

		// get NI
		value = convertToInt(parsedLine.at(16));
		procData[pidNums.at(i)]->setNI(value);

		// get S
		procData[pidNums.at(i)]->setS(lineString.at(0));

		// get %cpu for processes
		// (utime - stime)/(system uptime - process start time)
		// (col(14) - col(15))/(/proc/uptime(0) - col(22)
 		utime = convertToInt(parsedLine.at(11));
		cutime = convertToInt(parsedLine.at(12));
		pstart = convertToInt(parsedLine.at(19));
		newVal = (utime + cutime)/(uptime.getTotalSecs() - (pstart/100));

		// modify cpu% to xx.x
		newVal *= 10;
		intPercentage = newVal;
		
		if(intPercentage != 0)
		  {
		    newVal = intPercentage;
		    newVal = newVal/10;
		    procData[pidNums.at(i)]->setCPUUsage(newVal);
		  }
		else
		  {
		    procData[pidNums.at(i)]->setCPUUsage(0);
		  }
	      }

	    // ## get %CPU ##
	    const double ticks = (double)sysconf(_SC_CLK_TCK);
	    filePath = _PROC;
	    filePath.append(_STAT);
	    lineString = returnFileLineByNumber(filePath, 1);
	    parsedLine = parseLine(lineString);
	    cpuInfo.setUs(convertToInt(parsedLine.at(1)));
	    cpuInfo.setNi(convertToInt(parsedLine.at(2)));
	    cpuInfo.setSy(convertToInt(parsedLine.at(3)));
	    cpuInfo.setId(convertToInt(parsedLine.at(4)));
	    cpuInfo.setWa(convertToInt(parsedLine.at(5)));
	    cpuInfo.setIrq(convertToInt(parsedLine.at(6)));
	    cpuInfo.setSirq(convertToInt(parsedLine.at(7)));
	    cpuInfo.setSt(convertToInt(parsedLine.at(8)));
	    cpuInfo.setGu(convertToInt(parsedLine.at(9)));
	    cpuInfo.setGun(convertToInt(parsedLine.at(10)));
	    cpuInfo.setTicks(ticks);
	    cpuInfo.setJiffs(cpuInfo.calculateJiffs());
#if _CURSES	    
	    cpuWin.defineCPULine(doubleToStr(cpuInfo.getAvgUs(), 1),
				 doubleToStr(cpuInfo.getAvgSy(), 1),
				 doubleToStr(cpuInfo.getAvgNi(), 1),
				 doubleToStr(cpuInfo.getAvgId(), 1),
				 doubleToStr(cpuInfo.getAvgWa(), 1),
				 doubleToStr(cpuInfo.getAvgSt(), 1));
#endif	    
	    // outLines.push_back(memWin.getCPULine());

	    // memInfo data from /proc/meminfo
	    fileLine = returnFileLineByNumber(_PROC_MEMINFO, 1);
	    parsedLine = parseLine(fileLine);
	    memInfo.setMemTotal(convertToInt(parsedLine.at(1)));
	    fileLine = returnFileLineByNumber(_PROC_MEMINFO, 2);
	    parsedLine = parseLine(fileLine);
	    memInfo.setMemFree(convertToInt(parsedLine.at(1)));
	    fileLine = returnFileLineByNumber(_PROC_MEMINFO, 3);
	    parsedLine = parseLine(fileLine);
	    memInfo.setMemAvailable(convertToInt(parsedLine.at(1)));
	    fileLine = returnFileLineByNumber(_PROC_MEMINFO, 4);
	    parsedLine = parseLine(fileLine);
	    memInfo.setBuffers(convertToInt(parsedLine.at(1)));
	    fileLine = returnFileLineByNumber(_PROC_MEMINFO, 5);
	    parsedLine = parseLine(fileLine);
	    memInfo.setCached(convertToInt(parsedLine.at(1)));
	    fileLine = returnFileLineByNumber(_PROC_MEMINFO, 15);
	    parsedLine = parseLine(fileLine);
	    memInfo.setSwapTotal(convertToInt(parsedLine.at(1)));
	    fileLine = returnFileLineByNumber(_PROC_MEMINFO, 16);
	    parsedLine = parseLine(fileLine);
	    memInfo.setSwapFree(convertToInt(parsedLine.at(1)));
	    fileLine = returnFileLineByNumber(_PROC_MEMINFO, 26);
	    parsedLine = parseLine(fileLine);

#if _CURSES	    
	    memInfo.setSReclaimable(convertToInt(parsedLine.at(1)));
	    memInfo.setMemUsed(memInfo.calculateMemUsed());
	    memInfo.setSwapUsed(memInfo.calculateSwapUsed());
	    memInfo.setBuffCache(memInfo.calculateBuffCache());
	    memWin.setStringMiB(doubleToStr(KiBToMiB(memInfo.getMemTotal()), 1),
				doubleToStr(KiBToMiB(memInfo.getMemFree()), 1),
				doubleToStr(KiBToMiB(memInfo.getMemUsed()), 1),
				doubleToStr(KiBToMiB(memInfo.getBuffCache()), 1));
	    memWin.setStringSwap(doubleToStr(KiBToMiB(memInfo.getSwapTotal()), 1),
				 doubleToStr(KiBToMiB(memInfo.getSwapFree()), 1),
				 doubleToStr(KiBToMiB(memInfo.getSwapUsed()), 1),
				 doubleToStr(KiBToMiB(memInfo.getMemAvailable()), 1));
#endif
	    
	    // ## get process state count ##
	    unsigned int running;
	    unsigned int unSleep;
	    unsigned int inSleep;
	    unsigned int sleeping;
	    unsigned int stopped;
	    unsigned int zombie;
	    unsigned int idle;
	    unsigned int total;
 	    for(std::unordered_map<int, ProcessInfo*>::iterator it = procData.begin();
		it != procData.end(); it++)
	      {
		switch(it->second->getS())
		  {
		  case 'S':
		    inSleep++;
		    break;
		  case 'I':
		    idle++;
		    break;
		  case 'T':
		    stopped++;
		    break;
		  case 'D':
		    unSleep++;
		    break;
		  case 'R':
		    running++;
		    break;
		  case 'Z':
		    zombie++;
		    break;
		  default:
		    break;
		}
	      }

	    // save task data in object in case we want to use later
	    taskInfo.setRunning(running);
	    taskInfo.setUnSleep(unSleep);
	    taskInfo.setInSleep(inSleep);
	    taskInfo.setStopped(stopped);
	    taskInfo.setZombie(zombie);
	    taskInfo.setIdle(idle);
	    sleeping = inSleep + unSleep + idle;
	    total = running + sleeping;
	    taskInfo.setSleeping(sleeping);
	    taskInfo.setTotal(total);
	    // define the window line
	    tasksWin.defineTasksWindow(total,
				       running,
				       sleeping,
				       stopped,
				       zombie);
	    outLines.push_back(tasksWin.getTasksLine());
     }
    
    processInfo = nullptr;
    pidNumsOld.clear();

    // ## get user input ##
    std::vector<std::pair<double, int>> sortedByDouble;
    std::vector<std::pair<std::string, int>> procStrings;
    std::vector<std::pair<int, int>> sortedByInt;
    std::vector<int> outList;
    int highlightIndex = 0;
    int input = 0;
    int moveVal = 0;
    int previousSortState = sortState;
#if _CURSES
    moveVal = input = getch();
    flushinp();
#endif    

    if(input != -1)
      {
	if(progStates[input])
	  {
	    prevState = progState;
	    progState = input;
	  }
	else if(input == '<' && sortState > _PIDWIN)
	  {
	    if(highlight == true)
	      {
#if _CURSES		
		wattroff(allWins.at(sortState)->getWindow(),
			 A_BOLD);
	    	sortState--;
	    	wattron(allWins.at(sortState)->getWindow(),
	    		A_BOLD);
#endif	      
	      }
	    else
	      {
		sortState--;
	      }
	  }
	else if(input == '>' && sortState < _COMMANDWIN)
	  {
	    if(highlight == true)
	      {
#if _CURSES		
		wattroff(allWins.at(sortState)->getWindow(),
			 A_BOLD);
		sortState++;
		wattron(allWins.at(sortState)->getWindow(),
			A_BOLD);
#endif		
	      }
	    else
	      {
		sortState++;
	      }
	  }
      }

    // ## update states ##
    // change process state
    switch(progState)
      {
      case _PROGSTATEHELP: // help
	break;
      case _PROGSTATEQUIT: // quit
	quit = true;
	break;
      case _PROGSTATEHL: // highlight
	if(highlight == true)
	  {
	    highlight = false;
	  }
	else if(highlight == false)
	  {
	    highlight = true;
	  }
	progState = prevState;
	break;
      default:
	break;
      }

    highlightIndex = sortState;
    
    // change sort state
    switch(sortState)
      {
      case _PIDWIN:
	outList = pidNums;
	std::sort(outList.begin(),
		  outList.end());
	break;
      case _USERWIN:
	outList = sortByUSER(procData,
			     pidNums);
	break;
      case _PRWIN:
	outList = sortByPR(procData,
			   pidNums);
	break;
      case _NIWIN:
	outList = sortByNI(procData,
			   pidNums);
	break;
      case _VIRTWIN:
	outList = sortByVIRT(procData,
			     pidNums);
	break;
      case _RESWIN:
	outList = sortByRES(procData,
			    pidNums);
	break;
      case _SHRWIN:
	outList = sortBySHR(procData,
			    pidNums);
	break;
      case _SWIN:
	outList = sortByS(procData,
			  pidNums);
	break;
      case _PROCCPUWIN:
	outList = sortByCPUUSAGE(procData,
				 pidNums);	
	break;
      case _PROCMEMWIN:
	outList = pidNums;
	std::sort(outList.begin(),
		  outList.end());
	break;
      case _PROCTIMEWIN:
	outList = pidNums;
	std::sort(outList.begin(),
		  outList.end());	
	break;
      case _COMMANDWIN:
	outList = sortByCOMMAND(procData,
				pidNums);
	break;
      default:
	break;
      }
    
    // shift windows
    switch(moveVal)
      {
      case KEY_UP:
	if(shiftY < 1)
	  {
	    shiftY++;
	  }
	break;
      case KEY_DOWN:
	if(abs(shiftY) < outList.size() - 2)
	  {
	    shiftY--;
	  }
	break;
      case KEY_LEFT:
	if(shiftX > _PIDWIN)
	  {
#if _CURSES	    
	    shiftBottomWinsRight(allWins,
				 shiftX);
#endif	    
	    shiftX--;
	  }
	break;
      case KEY_RIGHT:
	if(shiftX < _COMMANDWIN)
	  {
#if _CURSES	    
	    shiftBottomWinsLeft(allWins,
				shiftX);
#endif	    
	    shiftX++;
	  }
	break;
      default:
	break;
      }
    
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
    
    printProcs(shiftY,
	       shiftX,
	       outList,
	       procData,
	       allWins);
    attronBottomWins(allWins,
		     _BLACK_TEXT);
    printWindowNames(allWins);
    attroffBottomWins(allWins,
		      _BLACK_TEXT);
    werase(mainWin.getWindow());
    printColorLine(allWins,
		   colorLine,
		   PIDWin.getStartY(),
		   _BLACK_TEXT);
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
