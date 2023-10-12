 /*
  File: main.cpp
  Version: V0.1

  Program Description: 
    A rendition of the Top program using C++. It is currently
    tested in Ubuntu and ArchLinux.  Each have a branch that corresponds to the
    working implementation.  The main branch contains a stable version that works
    on both operating systems.

  Notes:
  - Top's horizontal window scroll is determined by the total possible length
  of the value the column is representing until you reach command.  Once
  command is reached, every proceeding scroll is an 8 character window shift.

  Controls:
  - the 'x' key allows highlighting a particular column.
  - the arrow keys allow shifting the windows left and right.
  - the '<' and '>' keys change how the columns are sorted.

  Changes Needed:
  - highlight row when a change happens in the sorted value type
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
#include <algorithm>
#include "log.hpp"
#include "cursesWindow.hpp"
#include "mainWindow.hpp"
#include "topWindow.hpp"
#include "tasksWindow.hpp"
#include "VIRTWindow.hpp"
#include "COMMANDWindow.hpp"
#include "cpuWindow.hpp"
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
#include "progStateConsts.hpp"
#include "cursesWinConsts.hpp"
#include "fileConsts.hpp"
#include "sortProcessLists.hpp"

//constants
// debug
#define _DEBUG 0
#define _CURSES 1
#define _NOLOG 0

// commands and options/modes
#define _UTMPDUMP "utmpdump"
#define _READ "r"

// other WINDOW constants
#define _Y_OFFSET 6

// function prototypes
void printWindowToLog(std::ofstream& log,
		      const CursesWindow& win);



/*
  Function:
  main

  Description:
  The main driver function for the Bottom program.
 */
int main()
{
  //  ## create log system ##
  Log logFile("./log/", "log", 1, ".log");
  time_t rawtime;
  struct tm* timeinfo;
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

  // process related vars
  MemInfo mInfo;
  ProcessInfo* pInfo;
  std::vector<int> pidList;
  std::unordered_map<int, ProcessInfo*> pUmap;
  std::unordered_map<int, ProcessInfo*>::iterator pUmapIt;

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
  startY = _Y_OFFSET - 6;  
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
  // define tasks window
  numLines = 1;
  numCols = numCols;
  startY = _Y_OFFSET - 5;
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
  startY = _Y_OFFSET - 4;
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
  startY = _Y_OFFSET - 3;
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
  startY = memWin.getStartY() + _Y_OFFSET - 3;
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
  startY = memWin.getStartY() + _Y_OFFSET - 3;
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
  startY = memWin.getStartY() + _Y_OFFSET - 3;
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
  startY = memWin.getStartY() + _Y_OFFSET - 3;
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
  startY = memWin.getStartY() + _Y_OFFSET - 3;
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
  startY = memWin.getStartY() + _Y_OFFSET - 3;
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
  startY = memWin.getStartY() + _Y_OFFSET - 3;
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
  startY = memWin.getStartY() + _Y_OFFSET - 3;
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
  startY = memWin.getStartY() + _Y_OFFSET - 3;
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
  startY = memWin.getStartY() + _Y_OFFSET - 3;
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
  startY = memWin.getStartY() + _Y_OFFSET - 3;
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
  startY = memWin.getStartY() + _Y_OFFSET - 3;
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
    std::string outLine;
    std::string tempLine;
    std::string fileLine;
    std::vector<std::string> parsedLine;
    int val = 0;

    // get topWin data
    fileLine = returnFileLineByNumber(_UPTIME, 1);
    parsedLine = parseLine(fileLine);
    val = convertToInt(parsedLine.at(0));
    SecondsToTime uptime(val);
    outLine = "top - ";
    time(&rawtime);
    timeinfo = localtime(&rawtime);    
    outLine.append(uptime.returnHHMMSS(timeinfo->tm_hour,
				       timeinfo->tm_min,
				       timeinfo->tm_sec));
    outLine.append(" up ");
    val = uptime.getHours()/24;
    
    if(val == 1)
      {
	outLine.append(std::to_string(val));
	outLine.append(" day, ");
      }
    else if (val > 1)
      {
	val = uptime.getHours()/24;
	outLine.append(std::to_string(val));
	outLine.append(" days, ");
      }

    outLine.append(std::to_string(uptime.getHours() % 24));
    outLine.append(":");
    outLine.append(std::to_string(uptime.getMinutes()));
    outLine.append(", ");
    fileLine = returnLineFromPipe("users", _READ, 1);
    parsedLine = parseLine(fileLine);
    outLine.append(std::to_string(parsedLine.size()));
    outLine.append(" users, load average: ");
    fileLine = returnFileLineByNumber("/proc/loadavg", 1);
    parsedLine = parseLine(fileLine);
    outLine.append(parsedLine.at(0));
    outLine.append(" ");
    outLine.append(parsedLine.at(1));
    outLine.append(" ");
    outLine.append(parsedLine.at(2));

    // print topWin data window
#if _CURSES
    mvwaddstr(allWins.at(_TOPWIN)->getWindow(),	      
	      0,
	      0,
	      outLine.c_str());
#endif
    
    // ## find running processes and update the list if needed ##
    // store old process list
    std::vector<int> pidListOld(pidList);
    std::vector<int> pidListDead;

    // get new process list
    pidList.clear();
    pidList = (findNumericDirs(_PROC));
    std::sort(pidList.begin(), pidList.end());
    
    // find any dead processes
    for(int i = 0; i < pidListOld.size(); i++)
      {
	bool exists = false;
	
	for(int j = 0; j < pidList.size(); j++)
	  {
	    if(pidListOld.at(i) == pidList.at(j))
	      {
		exists = true;
		break;
	      }
	  }

	if(exists == false)
	  {
	    pidListDead.push_back(pidListOld.at(i));
	  }
      }

    // remove dead processes from the process umap
    for(int i = 0; i < pidListDead.size(); i++)
      {
	if(pUmap.count(pidListDead.at(i)) > 0)
	  {
	    delete(pUmap[pidListDead.at(i)]);
	    // log << "Deleted Process With PID: " << pidListDead.at(i) << std::endl;
	    pUmap.erase(pidListDead.at(i));
	  }
      }

    // update processes data
    for(int i = 0; i < pidList.size(); i++)
      {
	// if process is new, allocate it
	if(pUmap.count(pidList.at(i)) == 0)
	  {
	    pInfo = new ProcessInfo();
	    pUmap.insert(std::make_pair(pidList.at(i), pInfo));
	  }
	    std::string filePath;
	    std::string lineString;
	    const std::string currProc = _PROC + std::to_string(pidList.at(i));
	    unsigned int value = 0;
	    
	    // set pid
	    pUmap[pidList.at(i)]->setPID(pidList.at(i));
	    // log << std::endl << "PID: " << pidList.at(i) << std::endl;

	    // get command
	    filePath = currProc;
	    filePath.append(_COMM);
	    lineString = returnFileLineByNumber(filePath, 1);
	    pUmap[pidList.at(i)]->setCOMMAND(lineString);
	    // log << "COMM: " << pUmap[pidList.at(i)]->getCOMMAND() << std::endl;

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
		    log << "Failed to call getpwuid_r()" << std::endl;
		  }
		else
		  {
		    pUmap[pidList.at(i)]->setUSER(userData.pw_name);		    
		  }
	      }
	    else
	      {
		pUmap[pidList.at(i)]->setUSER("-1");
	      }

	    // get VIRT
	    lineString = returnFileLineByPhrase(filePath, "VmSize");
	    if(lineString != "-1")
	      {
		parsedLine = parseLine(lineString);
		value = convertToInt(parsedLine.at(1));
		pUmap[pidList.at(i)]->setVIRT(value);
	      }

	    // get RES
	    lineString = returnFileLineByPhrase(filePath, "VmRSS");
	    if(lineString != "-1")
	      {
		parsedLine = parseLine(lineString);
		value = convertToInt(parsedLine.at(1));
		pUmap[pidList.at(i)]->setRes(value);
	      }

	    // get SHR
	    lineString = returnFileLineByPhrase(filePath, "RssFile");
	    if(lineString != "-1")
	      {
		parsedLine = parseLine(lineString);
		value = convertToInt(parsedLine.at(1));
		pUmap[pidList.at(i)]->setSHR(value);
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
		pUmap[pidList.at(i)]->setCPUUsage(newVal);

		// get priority
		lineString = fixStatLine(lineString);
		parsedLine = parseLine(lineString);
		value = convertToInt(parsedLine.at(15));
		pUmap[pidList.at(i)]->setPR(value);

		// get NI
		value = convertToInt(parsedLine.at(16));
		pUmap[pidList.at(i)]->setNI(value);

		// get S
		pUmap[pidList.at(i)]->setS(lineString.at(0));

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
		    pUmap[pidList.at(i)]->setCPUUsage(newVal);
		  }
		else
		  {
		    pUmap[pidList.at(i)]->setCPUUsage(0);
		  }
	      }
	    
	    // ## get %CPU ##
	    const double ticks = (double)sysconf(_SC_CLK_TCK);
	    double avgUs = 0;
	    double avgSy = 0;
	    double avgNi = 0;
	    double avgId = 0;
	    double avgWa = 0;
	    double avgHi = 0;
	    double avgSi = 0;
	    double avgSt = 0;
	    double totalJiffs = 0;
	    double us = 0;
	    double ni = 0;
	    double sy = 0;
	    double id = 0;
	    double wa = 0;
	    double irq = 0;
	    double sirq = 0;
	    double hi = 0;
	    double si = 0;
	    double st = 0;
	    double gu = 0;
	    double gun = 0;
	    filePath = "/proc/stat";
	    lineString = returnFileLineByNumber(filePath, 1);
	    parsedLine = parseLine(lineString);
	    us = convertToInt(parsedLine.at(1));
	    ni = convertToInt(parsedLine.at(2));
	    sy = convertToInt(parsedLine.at(3));
	    id = convertToInt(parsedLine.at(4));
	    wa = convertToInt(parsedLine.at(5));
	    irq = convertToInt(parsedLine.at(6));
	    sirq = convertToInt(parsedLine.at(7));
	    st = convertToInt(parsedLine.at(8));
	    gu = convertToInt(parsedLine.at(9));
	    gun = convertToInt(parsedLine.at(10));
	    totalJiffs = us + ni + sy + id + wa + irq + sirq + st + gu + gun;
	    //	    avgUs = (ticks * us)/totalJiffs;
	    avgSy = (ticks * sy)/totalJiffs;
	    avgNi = (ticks * ni)/totalJiffs;
	    avgId = (ticks * id)/totalJiffs;
	    avgWa = (ticks * wa)/totalJiffs;
	    avgSt = (ticks * st)/totalJiffs;
	    avgUs = 100 - (avgId);
	    // avgHi = (100 * hi)/totalJiffs;
	    outLine = "%CPU(s): ";
	    outLine.append(doubleToStr(avgUs, 1));
	    outLine.append(" us, ");
	    outLine.append(doubleToStr(avgSy, 1));
	    outLine.append(" sy, ");
	    outLine.append(doubleToStr(avgNi, 1));
	    outLine.append(" ni, ");
	    outLine.append(doubleToStr(avgId, 1));
	    outLine.append(" id, ");
	    outLine.append(doubleToStr(avgWa, 1));
	    outLine.append(" wa, ");
	    outLine.append("N/A");
	    outLine.append(" si, ");
	    outLine.append(doubleToStr(avgSt, 1));
	    outLine.append(" st, ");

#if _CURSES
	    mvwaddstr(cpuWin.getWindow(),
		      0,
		      0,
		      outLine.c_str());
#endif
	    
	    // mInfo data from /proc/meminfo
	    fileLine = returnFileLineByNumber(_PROC_MEMINFO, 1);
	    parsedLine = parseLine(fileLine);
	    mInfo.setMemTotal(convertToInt(parsedLine.at(1)));
	    fileLine = returnFileLineByNumber(_PROC_MEMINFO, 2);
	    parsedLine = parseLine(fileLine);
	    mInfo.setMemFree(convertToInt(parsedLine.at(1)));
	    fileLine = returnFileLineByNumber(_PROC_MEMINFO, 3);
	    parsedLine = parseLine(fileLine);
	    mInfo.setMemAvailable(convertToInt(parsedLine.at(1)));
	    fileLine = returnFileLineByNumber(_PROC_MEMINFO, 4);
	    parsedLine = parseLine(fileLine);
	    mInfo.setBuffers(convertToInt(parsedLine.at(1)));
	    fileLine = returnFileLineByNumber(_PROC_MEMINFO, 5);
	    parsedLine = parseLine(fileLine);
	    mInfo.setCached(convertToInt(parsedLine.at(1)));
	    fileLine = returnFileLineByNumber(_PROC_MEMINFO, 15);
	    parsedLine = parseLine(fileLine);
	    mInfo.setSwapTotal(convertToInt(parsedLine.at(1)));
	    fileLine = returnFileLineByNumber(_PROC_MEMINFO, 16);
	    parsedLine = parseLine(fileLine);
	    mInfo.setSwapFree(convertToInt(parsedLine.at(1)));
	    fileLine = returnFileLineByNumber(_PROC_MEMINFO, 26);
	    parsedLine = parseLine(fileLine);
	    mInfo.setSReclaimable(convertToInt(parsedLine.at(1)));
	    mInfo.setMemUsed(mInfo.calculateMemUsed());
	    mInfo.setSwapUsed(mInfo.calculateSwapUsed());
	    mInfo.setBuffCache(mInfo.calculateBuffCache());
	    allWins.at(_MEMWIN)->setStringMiB(doubleToStr(KiBToMiB(mInfo.getMemTotal()), 1),
					      doubleToStr(KiBToMiB(mInfo.getMemFree()), 1),
					      doubleToStr(KiBToMiB(mInfo.getMemUsed()), 1),
					      doubleToStr(KiBToMiB(mInfo.getBuffCache()), 1));
	    allWins.at(_MEMWIN)->setStringSwap(doubleToStr(KiBToMiB(mInfo.getSwapTotal()), 1),
					       doubleToStr(KiBToMiB(mInfo.getSwapFree()), 1),
					       doubleToStr(KiBToMiB(mInfo.getSwapUsed()), 1),
					       doubleToStr(KiBToMiB(mInfo.getMemAvailable()), 1));

#if _CURSES
	    // print memWin data to window
	    mvwaddstr(allWins.at(_MEMWIN)->getWindow(),
		      0,
		      0,
		      memWin.getMiB().c_str());
	    mvwaddstr(allWins.at(_MEMWIN)->getWindow(),
		      1,
		      0,
		      memWin.getSwap().c_str());
#endif

	    // ## get process state count ##
	    unsigned int running = 0;
	    unsigned int unSleep = 0;
	    unsigned int inSleep = 0;
	    unsigned int sleeping = 0;
	    unsigned int stopped = 0;
	    unsigned int zombie = 0;
	    unsigned int idle = 0;
	    unsigned int total = 0;

 	    for(std::unordered_map<int, ProcessInfo*>::iterator it = pUmap.begin();
		it != pUmap.end(); it++)
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

	    // output the "tasks" line
	    sleeping = inSleep + unSleep + idle;
	    total = running + sleeping;
	    outLine = "Tasks: ";
	    outLine.append(std::to_string(total));
	    outLine.append(" total, ");
	    outLine.append(std::to_string(running));
	    outLine.append(" running, ");
	    outLine.append(std::to_string(sleeping));
	    outLine.append(" sleeping, ");
	    outLine.append(std::to_string(stopped));
	    outLine.append(" stopped, ");
	    outLine.append(std::to_string(zombie));
	    outLine.append(" zombie");
#if _CURSES
	    mvwaddstr(tasksWin.getWindow(),
		      0,
		      0,
		      outLine.c_str());
#endif
      }
    
    pInfo = nullptr;
    pidListOld.clear();

    // ## get user input ##
    std::vector<std::pair<double, int>> sortedByDouble;
    std::vector<std::pair<std::string, int>> sortedByString;
    std::vector<std::pair<int, int>> sortedByInt;
    std::vector<int> outList;
    int highlightIndex = 0;
    int input = 0;
    int moveVal = 0;

    moveVal = input = getch();

    if(input != -1)
      {
	if(progStates[input])
	  {
	    prevState = progState;
	    progState = input;
	  }
	else if(input == '<' && sortState > _PIDWIN)
	  {
	    sortState--;
	  }
	else if(input == '>' && sortState < _COMMANDWIN)
	  {
	    sortState++;
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

    // change sort state
    switch(sortState)
      {
      case _PIDWIN: // PID
	highlightIndex = _PIDWIN;
	std::reverse(pidList.begin(),pidList.end());
	outList = pidList;
	break;
      case _USERWIN: // USER
	highlightIndex = _USERWIN;
	outList = pidList;
	break;
      case _PRWIN: // PR
	highlightIndex = _PRWIN;
	for(int i = 0; i < pUmap.size(); i++)
	  {
	    const int temp = pUmap[pidList.at(i)]->getPR();

	    if(temp != 0)
	      {
		sortedByInt.push_back(std::make_pair(temp, pidList.at(i)));
	      }
	  }
	std::sort(sortedByInt.begin(), sortedByInt.end());
	outList = mergeIntLists(sortedByInt,
			       pidList,
			       pUmap);
	break;
      case _NIWIN: // NI
	highlightIndex = _NIWIN;
	for(int i = 0; i < pUmap.size(); i++)
	  {
	    const int temp = pUmap[pidList.at(i)]->getNI();

	    if(temp != 0)
	      {
		sortedByInt.push_back(std::make_pair(temp, pidList.at(i)));
	      }
	  }
	std::sort(sortedByInt.begin(), sortedByInt.end());
	outList = mergeIntLists(sortedByInt,
			       pidList,
			       pUmap);
	break;
      case _VIRTWIN: // VIRT
	highlightIndex = _VIRTWIN;
	for(int i = 0; i < pUmap.size(); i++)
	  {
	    const int temp = pUmap[pidList.at(i)]->getVIRT();

	    if(temp != 0)
	      {
		sortedByInt.push_back(std::make_pair(temp, pidList.at(i)));
	      }
	  }
	std::sort(sortedByInt.begin(), sortedByInt.end());
	outList = mergeIntLists(sortedByInt,
			       pidList,
			       pUmap);
	break;
      case _RESWIN: // RES
	highlightIndex = _RESWIN;
	for(int i = 0; i < pUmap.size(); i++)
	  {
	    const int temp = pUmap[pidList.at(i)]->getRES();

	    if(temp != 0)
	      {
		sortedByInt.push_back(std::make_pair(temp, pidList.at(i)));
	      }
	  }
	std::sort(sortedByInt.begin(), sortedByInt.end());
	outList = mergeIntLists(sortedByInt,
			       pidList,
			       pUmap);
	break;
      case _SHRWIN: // SHR
	highlightIndex = _SHRWIN;
	for(int i = 0; i < pUmap.size(); i++)
	  {
	    const int temp = pUmap[pidList.at(i)]->getSHR();

	    if(temp != 0)
	      {
		sortedByInt.push_back(std::make_pair(temp, pidList.at(i)));
	      }
	  }
	std::sort(sortedByInt.begin(), sortedByInt.end());
	outList = mergeIntLists(sortedByInt,
			       pidList,
			       pUmap);
	break;
      case _SWIN: // S
	highlightIndex = _SWIN;
	for(int i = 0; i < pUmap.size(); i++)
	  {
	    const int temp = pUmap[pidList.at(i)]->getS();

	    if(temp != 0)
	      {
		sortedByInt.push_back(std::make_pair(temp, pidList.at(i)));
	      }
	  }
	std::sort(sortedByInt.begin(), sortedByInt.end());
	outList = mergeIntLists(sortedByInt,
			       pidList,
			       pUmap);
	break;
      case _PROCCPUWIN: // %CPU
	highlightIndex = _PROCCPUWIN;
	for(int i = 0; i < pUmap.size(); i++)
	  {
	    const double temp = pUmap[pidList.at(i)]->getCPUUsage();

	    if(temp != 0)
	      {
		sortedByDouble.push_back(std::make_pair(temp, pidList.at(i)));
	      }
	  }
	std::sort(sortedByDouble.begin(), sortedByDouble.end());
	outList = mergeDoubleLists(sortedByDouble,
				  pidList,
				  pUmap);
	break;
      case _PROCMEMWIN: // %MEM
	highlightIndex = _PROCMEMWIN;
	for(int i = 0; i < pUmap.size(); i++)
	  {
	    const double temp = pUmap[pidList.at(i)]->getMEMUsage();

	    if(temp != 0)
	      {
		sortedByDouble.push_back(std::make_pair(temp, pidList.at(i)));
	      }
	  }
	std::sort(sortedByDouble.begin(), sortedByDouble.end());
	outList = mergeDoubleLists(sortedByDouble,
				pidList,
				pUmap);
	break;	
      case _PROCTIMEWIN: // TIME+
	highlightIndex = _PROCTIMEWIN;
	outList = pidList;
	break;
      case _COMMANDWIN: // COMMAND
	highlightIndex = _COMMANDWIN;
	for(int i = 0; i < pUmap.size(); i++)
	  {
	    const std::string temp = pUmap[pidList.at(i)]->getCOMMAND();

	    if(temp != "")
	      {
		sortedByString.push_back(std::make_pair(temp, pidList.at(i)));
	      }
	  }

	std::sort(sortedByString.begin(), sortedByString.end());
	outList = mergeStringLists(sortedByString,
				  pidList,
				  pUmap);
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
	if(std::abs(shiftY) < pUmap.size() - 1)
	  {
	    shiftY--;
	  }
	break;
      case KEY_LEFT:
	if(shiftX > _PIDWIN)
	  {
	    shiftBottomWinsRight(allWins,
				 shiftX);
	    shiftX--;
	  }
	break;
      case KEY_RIGHT:
	if(shiftX < _COMMANDWIN)
	  {
	    shiftBottomWinsLeft(allWins,
				shiftX);
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
	       pUmap,
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
