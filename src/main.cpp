/*
  File: main.c

  Program Description: A rendition of the Top program.

  Details:
  V0.1

  Notes:
  - Top's horizontal window scroll is determined by the total possible length
    of the value the column is representing until you reach command.  Once
    command is reached, every proceeding scroll is an 8 character window shift.

  To Add:
  - Wrapper functions for the curse calls with error handling
  - could use a counter for up/down left/right arrow clicks for starting point
    in array.
 
  Potential Future Additions:
  - mouse functionality option which would then pop up a window with buttons
    to click
  - make the help menu more user friendly
  - could leverage internet connectivity.
  * pull our processes and check if any are considered melicious
  against a database.
  - could prompt chapGPT
  - scan /var/log/wtmp  /var/run/utmp /var/log/btmp  for intrusions
  *same as above
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
#include <pwd.h>
#include <algorithm>
#include "log.hpp"
#include "cursesWindow.hpp"
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


//constants
// debug
#define _DEBUG 1
#define _CURSES 1
#define _NOLOG 0

// directories and files
#define _PROC "/proc/"
#define _COMM "/comm"
#define _STAT "/stat"
#define _STATUS "/status"
#define _MEMINFO "/meminfo"
#define _PROC_MEMINFO "/proc/meminfo"
#define _UPTIME "/proc/uptime"
#define _UTMP "/var/run/utmp"

// in-file phrases
#define _MEMTOTAL "MemTotal"
#define _MEMFREE "MemFree"
#define _BUFFERS "Buffers"
#define _CACHED "Cached"
#define _SRECLAIMABLE "SReclaimable"
#define _SWAPTOTAL "SwapTotal"
#define _SWAPFREE "SwapFree"
#define _MEMAVAILABLE "MemAvailable"

// commands and options/modes
#define _UTMPDUMP "utmpdump"
#define _READ "r"


// function prototypes
void printWindowToLog(std::ofstream& log,
		      const CursesWindow& win);



/*
  Function:
  main

  Description:
  The main driver file for the Bottom program.
 */
int main()
{
  //  ## create log system ##
  Log logFile("./log/", "log", 0, ".log");
  time_t rawtime;
  struct tm* timeinfo;
  std::ofstream log;

  //  get time info
  time(&rawtime);
  timeinfo = localtime(&rawtime);

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

  // variables
  CursesWindow processWin;
  MemInfo mInfo;
  ProcessInfo* pInfo;
  struct passwd* userData;
  std::unordered_map<int, ProcessInfo*> processesMap;
  std::unordered_map<int, ProcessInfo*>::iterator procIt;
  std::vector<std::string> parsedFileNames;
  std::vector<int> pidList;
  SecondsToTime uptime;
  short numLines = 0;
  short numCols = 0;
  short maxWindowY = 0;
  short maxWindowX = 0;
  short minWindowY = 0;
  short minWindowX = 0;
  short centerY = 0;
  short centerX = 0;
  short startY = 0;
  short startX = 0;
  short currentY = 0;
  short currentX = 0;
  short previousY = 0;
  short previousX = 0;

  // ## setup the main window ##
  CursesWindow mainWin;
  
  // init curses to main window
  mainWin.setWindow(initscr());
#if _CURSES
  // get main window dimensions
  getmaxyx(mainWin.getWindow(), numLines, numCols);

  // define the main window
  maxWindowY = numLines;
  maxWindowX = numCols;
  minWindowY = 0;
  minWindowX = 0;
  centerY = numLines/2;
  centerX = numCols/2;
  startY = 0;
  startX = 0;
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;
  
  mainWin.defineWindow("Main",
		       numLines,
		       numCols,
		       maxWindowY,
		       maxWindowX,
		       minWindowY,
		       minWindowX,
		       centerY,
		       centerX,
		       startY,
		       startX,
		       currentY,
		       currentX,
		       previousY,
		       previousX);
#endif
  
  // disable echoing characters to the window from getch();
  noecho();
  
  // make typed characters immediately available to program
  // (override part of the tty driver protocol)
  cbreak();

  // disable keyboard cursor visibility
  curs_set(false);

  // disable curses defined key values for getch() to mainWin
  keypad(mainWin.getWindow(), false);

  //
  nodelay(mainWin.getWindow(), true);


#if _CURSES
  // ## define windows ##
  // define top window
  numLines = 1;
  numCols = numCols;
  maxWindowY = 1;
  maxWindowX = numCols;
  minWindowY = 1;
  minWindowX = 0;
  centerY = 1;
  centerX = numCols/2;
  startY = 0;
  startX = 0;
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;

  TopWindow topWin("top",
		   numLines,
		   numCols,
		   maxWindowY,
		   maxWindowX,
		   minWindowY,
		   minWindowX,
		   centerY,
		   centerX,
		   startY,
		   startX,
		   currentY,
		   currentX,
		   previousY,
		   previousX);

  // define tasks window
  numLines = 1;
  numCols = numCols;
  maxWindowY = 1;
  maxWindowX = numCols;
  minWindowY = 1;
  minWindowX = 0;
  centerY = 2;
  centerX = numCols/2;
  startY = 1;
  startX = 0;
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;

  TasksWindow tasksWin("Tasks",
		       numLines,
		       numCols,
		       maxWindowY,
		       maxWindowX,
		       minWindowY,
		       minWindowX,
		       centerY,
		       centerX,
		       startY,
		       startX,
		       currentY,
		       currentX,
		       previousY,
		       previousX);

  // define cpu window
  numLines = 1;
  numCols = numCols;
  maxWindowY = 1;
  maxWindowX = numCols;
  minWindowY = 1;
  minWindowX = 0;
  centerY = 2;
  centerX = numCols/2;
  startY = 2;
  startX = 0;
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;

  CpuWindow cpuWin("CPU",
		   numLines,
		   numCols,
		   maxWindowY,
		   maxWindowX,
		   minWindowY,
		   minWindowX,
		   centerY,
		   centerX,
		   startY,
		   startX,
		   currentY,
		   currentX,
		   previousY,
		   previousX);

  // define mem window
  numLines = 2;
  numCols = numCols;
  maxWindowY = 2;
  maxWindowX = numCols;
  minWindowY = 1;
  minWindowX = 0;
  centerY = numLines/2;
  centerX = numCols/2;
  startY = 3;
  startX = 0;
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;

  MemWindow memWin("MEM",
		   numLines,
		   numCols,
		   maxWindowY,
		   maxWindowX,
		   minWindowY,
		   minWindowX,
		   centerY,
		   centerX,
		   startY,
		   startX,
		   currentY,
		   currentX,
		   previousY,
		   previousX);

  // define PID window
  /*
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
  */
  numLines = 1000;
  numCols = 7;
  maxWindowY = 0; 
  maxWindowX = 0;
  minWindowY = 0;
  minWindowX = 0;
  centerY = numLines/2;
  centerX = numCols/2;
  startY = memWin.getStartY() + 3;  // can be optimized by adding levels above instead of constant
  startX = 0;
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;

  PIDWindow PIDWin("PID",
		   numLines,
		   numCols,
		   maxWindowY,
		   maxWindowX,
		   minWindowY,
		   minWindowX,
		   centerY,
		   centerX,
		   startY,
		   startX,
		   currentY,
		   currentX,
		   previousY,
		   previousX);

  // define USER window
  /*
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
  */
  numLines = 1000;
  numCols = 8;
  maxWindowY = 0;
  maxWindowX = 0;
  minWindowY = 0;
  minWindowX = 0;
  centerY = numLines/2;
  centerX = numCols/2;
  startY = memWin.getStartY() + 3;
  startX = PIDWin.getNumCols() + 1;
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;

  USERWindow USERWin("USER",
		     numLines,
		     numCols,
		     maxWindowY,
		     maxWindowX,
		     minWindowY,
		     minWindowX,
		     centerY,
		     centerX,
		     startY,
		     startX,
		     currentY,
		     currentX,
		     previousY,
		     previousX);

  // define PR window
  /*
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
  */
  numLines = 1000;  
  numCols = 3;
  maxWindowY = 0;
  maxWindowX = 0;
  minWindowY = 0;
  minWindowX = 0;
  centerY = numLines/2;
  centerX = numCols/2;
  startY = memWin.getStartY() + 3;
  startX = PIDWin.getNumCols() + USERWin.getNumCols() + 2;
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;

  PRWindow PRWin("PR",
		 numLines,
		 numCols,
		 maxWindowY,
		 maxWindowX,
		 minWindowY,
		 minWindowX,
		 centerY,
		 centerX,
		 startY,
		 startX,
		 currentY,
		 currentX,
		 previousY,
		 previousX);

  // define NI window
  /*
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
  */
  numLines = 1000;
  numCols = 3;
  maxWindowY = 0;
  maxWindowX = 0;
  minWindowY = 0;
  minWindowX = 0;
  centerY = numLines/2;
  centerX = numCols/2;
  startY = memWin.getStartY() + 3;
  startX = PIDWin.getNumCols() + USERWin.getNumCols() + PRWin.getNumCols() + 3;
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;

  NIWindow NIWin("NI",
		 numLines,
		 numCols,
		 maxWindowY,
		 maxWindowX,
		 minWindowY,
		 minWindowX,
		 centerY,
		 centerX,
		 startY,
		 startX,
		 currentY,
		 currentX,
		 previousY,
		 previousX);

  // define VIRT window
  /*
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
  */
  numLines = 1000;
  numCols = 7;
  maxWindowY = 0;
  maxWindowX = 0;
  minWindowY = 0;
  minWindowX = 0;
  centerY = numLines/2;
  centerX = numCols/2;
  startY = memWin.getStartY() + 3;
  startX = PIDWin.getNumCols() +
           USERWin.getNumCols() +
           PRWin.getNumCols() +
    NIWin.getNumCols() + 4;
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;

  VIRTWindow VIRTWin("VIRT",
		     numLines,
		     numCols,
		     maxWindowY,
		     maxWindowX,
		     minWindowY,
		     minWindowX,
		     centerY,
		     centerX,
		     startY,
		     startX,
		     currentY,
		     currentX,
		     previousY,
		     previousX);

  // define RES window
  /*
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
  */
  numLines = 1000;
  numCols = 6;
  maxWindowY = 0;
  maxWindowX = 0;
  minWindowY = 0;
  minWindowX = 0;
  centerY = numLines/2;
  centerX = numCols/2;
  startY = memWin.getStartY() + 3;
  startX = PIDWin.getNumCols() +
           USERWin.getNumCols() +
           PRWin.getNumCols() +
           NIWin.getNumCols() +
           VIRTWin.getNumCols() + 5;
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;

  RESWindow RESWin("RES",
		   numLines,
		   numCols,
		   maxWindowY,
		   maxWindowX,
		   minWindowY,
		   minWindowX,
		   centerY,
		   centerX,
		   startY,
		   startX,
		   currentY,
		   currentX,
		   previousY,
		   previousX);

  // define SHR window
  /*
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
  */
  numLines = 1000;
  numCols = 6;
  maxWindowY = 0;
  maxWindowX = 0;
  minWindowY = 0;
  minWindowX = 0;
  centerY = numLines/2;
  centerX = numCols/2;
  startY = memWin.getStartY() + 3;
  startX = PIDWin.getNumCols() +
           USERWin.getNumCols() +
           PRWin.getNumCols() +
           NIWin.getNumCols() +
           VIRTWin.getNumCols() +
           RESWin.getNumCols() + 6;
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;

  SHRWindow SHRWin("SHR",
		   numLines,
		   numCols,
		   maxWindowY,
		   maxWindowX,
		   minWindowY,
		   minWindowX,
		   centerY,
		   centerX,
		   startY,
		   startX,
		   currentY,
		   currentX,
		   previousY,
		   previousX);

  // define S window
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
  numCols = 1;
  maxWindowY = 0;
  maxWindowX = 0;
  minWindowY = 0;
  minWindowX = 0;
  centerY = numCols/2;
  centerX = numCols/2;
  startY = memWin.getStartY() + 3;
  startX = PIDWin.getNumCols() +
           USERWin.getNumCols() +
           PRWin.getNumCols() +
           NIWin.getNumCols() +
           VIRTWin.getNumCols() +
           RESWin.getNumCols() +
           SHRWin.getNumCols() + 7;
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;

  SWindow SWin("S",
	       numLines,
	       numCols,
	       maxWindowY,
	       maxWindowX,
	       minWindowY,
	       minWindowX,
	       centerY,
	       centerX,
	       startY,
	       startX,
	       currentY,
	       currentX,
	       previousY,
	       previousX);

  // define PercentCPU window
  /*
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
  */
  numLines = 1000;
  numCols = 5;
  maxWindowY = 0;
  maxWindowX = 0;
  minWindowY = 0;
  minWindowX = 0;
  centerY = numCols/2;
  centerX = numCols/2;
  startY = memWin.getStartY() + 3;
  startX = PIDWin.getNumCols() +
           USERWin.getNumCols() +
           PRWin.getNumCols() +
           NIWin.getNumCols() +
           VIRTWin.getNumCols() +
           RESWin.getNumCols() +
           SHRWin.getNumCols() + 
           SWin.getNumCols() + 8;
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;

  PercentCPUWindow PercentCPUWin("%CPU",
				 numLines,
				 numCols,
				 maxWindowY,
				 maxWindowX,
				 minWindowY,
				 minWindowX,
				 centerY,
				 centerX,
				 startY,
				 startX,
				 currentY,
				 currentX,
				 previousY,
				 previousX);

  // define PercentMEM window
  /*
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
  */
  numLines = 1000;
  numCols = 5;
  maxWindowY = 0;
  maxWindowX = 0;
  minWindowY = 0;
  minWindowX = 0;
  centerY = numCols/2;
  centerX = numCols/2;
  startY = memWin.getStartY() + 3;
  startX = PIDWin.getNumCols() +
           USERWin.getNumCols() +
           PRWin.getNumCols() +
           NIWin.getNumCols() +
           VIRTWin.getNumCols() +
           RESWin.getNumCols() +
           SHRWin.getNumCols() + 
           SWin.getNumCols() +
           PercentCPUWin.getNumCols() + 9;
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;

  PercentMEMWindow PercentMEMWin("%MEM",
				 numLines,
				 numCols,
				 maxWindowY,
				 maxWindowX,
				 minWindowY,
				 minWindowX,
				 centerY,
				 centerX,
				 startY,
				 startX,
				 currentY,
				 currentX,
				 previousY,
				 previousX);

  // define TIME window
  /*
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
  */
  numLines = 1000;
  numCols = 9;
  maxWindowY = 0;
  maxWindowX = 0;
  minWindowY = 0;
  minWindowX = 0;
  centerY = numCols/2;
  centerX = numCols/2;
  startY = memWin.getStartY() + 3;
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
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;

  TIMEWindow TIMEWin("TIME+",
		     numLines,
		     numCols,
		     maxWindowY,
		     maxWindowX,
		     minWindowY,
		     minWindowX,
		     centerY,
		     centerX,
		     startY,
		     startX,
		     currentY,
		     currentX,
		     previousY,
		     previousX);

  // define COMMAND window
  /*
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
  */
  numLines = 1000;
  numCols = 1000;
  maxWindowY = 0;
  maxWindowX = 0;
  minWindowY = 0;
  minWindowX = 0;
  centerY = numCols/2;
  centerX = numCols/2;
  startY = memWin.getStartY() + 3;
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
  //  numCols = mainWin.getMaxWindowX() - startX;
  currentY = 0;
  currentX = 0;
  previousY = 0;
  previousX = 0;

  CursesWindow COMMANDWin("COMMAND",
			  numLines,
			  numCols,
			  maxWindowY,
			  maxWindowX,
			  minWindowY,
			  minWindowX,
			  centerY,
			  centerX,
			  startY,
			  startX,
			  currentY,
			  currentX,
			  previousY,
			  previousX);
  
  // ## create windows ##
  topWin.setWindow(newwin(topWin.getNumLines(),
			  topWin.getNumCols(),
			  topWin.getStartY(),
			  topWin.getStartX()));
  tasksWin.setWindow(newwin(tasksWin.getNumLines(),
			   tasksWin.getNumCols(),
			   tasksWin.getStartY(),
			   tasksWin.getStartX()));
  cpuWin.setWindow(newwin(cpuWin.getNumLines(),
			  cpuWin.getNumCols(),
			  cpuWin.getStartY(),
			  cpuWin.getStartX()));
  memWin.setWindow(newwin(memWin.getNumLines(),
			  memWin.getNumCols(),
			  memWin.getStartY(),
			  memWin.getStartX()));
  PIDWin.setWindow(newwin(PIDWin.getNumLines(),
			  PIDWin.getNumCols(),
			  PIDWin.getStartY(),
			  PIDWin.getStartX()));
  USERWin.setWindow(newwin(USERWin.getNumLines(),
			   USERWin.getNumCols(),
			   USERWin.getStartY(),
			   USERWin.getStartX()));
  PRWin.setWindow(newwin(PRWin.getNumLines(),
			 PRWin.getNumCols(),
			 PRWin.getStartY(),
			 PRWin.getStartX()));
  NIWin.setWindow(newwin(NIWin.getNumLines(),
			 NIWin.getNumCols(),
			 NIWin.getStartY(),
			 NIWin.getStartX()));
  VIRTWin.setWindow(newwin(VIRTWin.getNumLines(),
			   VIRTWin.getNumCols(),
			   VIRTWin.getStartY(),
			   VIRTWin.getStartX()));		  
  RESWin.setWindow(newwin(RESWin.getNumLines(),
			  RESWin.getNumCols(),
			  RESWin.getStartY(),
			  RESWin.getStartX()));
  SHRWin.setWindow(newwin(SHRWin.getNumLines(),
			  SHRWin.getNumCols(),
			  SHRWin.getStartY(),
			  SHRWin.getStartX()));
  SWin.setWindow(newwin(SWin.getNumLines(),
			SWin.getNumCols(),
			SWin.getStartY(),
			SWin.getStartX()));
  PercentCPUWin.setWindow(newwin(PercentCPUWin.getNumLines(),
				 PercentCPUWin.getNumCols(),
				 PercentCPUWin.getStartY(),
				 PercentCPUWin.getStartX()));
  PercentMEMWin.setWindow(newwin(PercentMEMWin.getNumLines(),
				 PercentMEMWin.getNumCols(),
				 PercentMEMWin.getStartY(),
				 PercentMEMWin.getStartX()));  
  TIMEWin.setWindow(newwin(TIMEWin.getNumLines(),
			   TIMEWin.getNumCols(),
			   TIMEWin.getStartY(),
			   TIMEWin.getStartX()));
  COMMANDWin.setWindow(newwin(COMMANDWin.getNumLines(),
			      COMMANDWin.getNumCols(),
			      COMMANDWin.getStartY(),
			      COMMANDWin.getStartX()));

  // draw window borders
  box(topWin.getWindow(), 'A', 'A');
  box(tasksWin.getWindow(), 'B', 'B');
  box(cpuWin.getWindow(), 'C', 'C');
  box(memWin.getWindow(), 'D', 'D');
  box(PIDWin.getWindow(), 'P', 'P');
  box(USERWin.getWindow(), 'E', 'E');
  box(PRWin.getWindow(), 'F', 'F');
  box(NIWin.getWindow(), 'G', 'G');
  box(VIRTWin.getWindow(), 'H', 'H');
  box(RESWin.getWindow(), 'I', 'I');
  box(SHRWin.getWindow(), 'J', 'J');
  box(SWin.getWindow(), 'K', 'K');
  box(PercentCPUWin.getWindow(), 'L', 'L');
  box(PercentMEMWin.getWindow(), 'M', 'M');
  box(TIMEWin.getWindow(), 'N', 'N');
  box(COMMANDWin.getWindow(), 'O', 'O');
  
  // ## for testing ##
  if(has_colors())
    {
      use_default_colors();
      //init_pair(-1);
      //init_color(COLOR_BLACK, 0, 0, 0);
      color_set(0, NULL);
    }
#endif

  // ## run the main program loop ##

  do{
    std::string outLine;
    std::string tempLine;
    std::string fileLine;
    std::vector<std::string> parsedLine;
    int val = 0;

#if _CURSES
    // clear the windows
    // erase();
    // get topWin data and print to screen
    /*
    topWin.setUptime(returnLineFromPipe("uptime", _READ, 1));
    mvwaddstr(topWin.getWindow(),
	      0,
	      0,
	      topWin.getUptime().c_str());
    */
    fileLine = returnFileLineByNumber(_UPTIME, 1);
    parsedLine = parseLine(fileLine);
    val = convertToInt(parsedLine.at(0));
    uptime.setHours(uptime.convertToHours(val));
    uptime.setMinutes(uptime.convertToMinutes(val));
    uptime.setSeconds(uptime.findRemainingSeconds(val));
    outLine = uptime.returnHHMMSS(timeinfo->tm_hour,
				  timeinfo->tm_min,
				  timeinfo->tm_sec);
    outLine.append(" up ");
    outLine.append(std::to_string(uptime.getHours()));
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

    log << outLine << std::endl;
    
    break;
    
    
#endif

    // get memory data from /proc/meminfo
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

#if _CURSES
    
    // set mem window data
    memWin.setStringMiB(std::to_string(mInfo.getMemTotal()),
			std::to_string(mInfo.getMemFree()),
			std::to_string(mInfo.getMemUsed()),
			std::to_string(mInfo.getBuffCache()));
    memWin.setStringSwap(std::to_string(mInfo.getSwapTotal()),
			 std::to_string(mInfo.getSwapFree()),
			 std::to_string(mInfo.getSwapUsed()),
			 std::to_string(mInfo.getMemAvailable()));
    
    // output the mem windows to curses
    mvwaddstr(memWin.getWindow(),
	      0,
	      0,
	      memWin.getMiB().c_str());
    mvwaddstr(memWin.getWindow(),
	      1,
	      0,
	      memWin.getSwap().c_str());
#endif    

    // ## handle processes ##
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
	if(processesMap.count(pidListDead.at(i)) > 0)
	  {
	    delete(processesMap[pidListDead.at(i)]);
	    log << "Deleted Process With PID: " << pidListDead.at(i) << std::endl;
	    processesMap.erase(pidListDead.at(i));
	  }
      }

    // update processes data
    for(int i = 0; i < pidList.size(); i++)
      {
	// if process is new, allocate it
	if(processesMap.count(pidList.at(i)) == 0)
	  {
	    pInfo = new ProcessInfo();
	    processesMap.insert(std::make_pair(pidList.at(i), pInfo));
	  }
	    std::string filePath;
	    std::string lineString;
	    const std::string currProc = _PROC + std::to_string(pidList.at(i));
	    int value = 0;
	    
	    // set pid
	    processesMap[pidList.at(i)]->setPID(pidList.at(i));
	    //	    log << std::endl << "PID: " << pidList.at(i) << std::endl;

	    // get command
	    filePath = currProc;
	    filePath.append(_COMM);
	    lineString = returnFileLineByNumber(filePath, 1);
	    processesMap[pidList.at(i)]->setCommand(lineString);
	    //	     log << "COMM: " << processesMap[pidList.at(i)]->getCommand() << std::endl;

 	    // get USER
	    filePath = currProc;
	    filePath.append(_STATUS);
	    lineString = returnPhraseLine(filePath, "Gid");
	    if(lineString != "-1")
	      {
		parsedLine = parseLine(lineString);
		value = convertToInt(parsedLine.at(1));
		userData = getpwuid(value);
		processesMap[pidList.at(i)]->setUser(userData->pw_name);
	      }

	    // get VIRT
	    lineString = returnFileLineByPhrase(filePath, "VmSize");
	    if(lineString != "-1")
	      {
		parsedLine = parseLine(lineString);
		value = convertToInt(parsedLine.at(1));
		processesMap[pidList.at(i)]->setVirt(value);
	      }

	    // get RES
	    lineString = returnFileLineByPhrase(filePath, "VmRSS");
	    if(lineString != "-1")
	      {
		parsedLine = parseLine(lineString);
		value = convertToInt(parsedLine.at(1));
		processesMap[pidList.at(i)]->setRes(value);
	      }

	    // get SHR
	    lineString = returnFileLineByPhrase(filePath, "RssFile");
	    if(lineString != "-1")
	      {
		parsedLine = parseLine(lineString);
		value = convertToInt(parsedLine.at(1));
		processesMap[pidList.at(i)]->setSHR(value);
	      }


 	    // get PR
	    filePath = currProc;
	    filePath.append(_STAT);
	    lineString = returnFileLineByNumber(filePath, 1);
	    if(lineString != "-1")
	      {
		lineString = fixStatLine(lineString);
		parsedLine = parseLine(lineString);
		value = convertToInt(parsedLine.at(15));
		processesMap[pidList.at(i)]->setPR(value);

		// get NI
		value = convertToInt(parsedLine.at(16));
		processesMap[pidList.at(i)]->setNI(value);

		// get S
		processesMap[pidList.at(i)]->setS(lineString.at(0));
	      }

	    // get %CPU
	    
	    // print extracted process data
	    /*
	    log << std::endl << "PID: " << processesMap[pidList.at(i)]->getPID() << std::endl
		<< "COMM: " << processesMap[pidList.at(i)]->getCommand() << std::endl
		<< "USER: " << processesMap[pidList.at(i)]->getUser() << std::endl
		<< "PR: " << processesMap[pidList.at(i)]->getPR() << std::endl
		<< "NI: " << processesMap[pidList.at(i)]->getNI() << std::endl
		<< "VIRT: " << processesMap[pidList.at(i)]->getVirt() << std::endl
		<< "RES: " << processesMap[pidList.at(i)]->getRes() << std::endl
		<< "SHR: " << processesMap[pidList.at(i)]->getSHR() << std::endl
		<< "S: " << processesMap[pidList.at(i)]->getS() << std::endl;
	    */
	    
	    /*
	    << "%CPU: " << processesMap[pidList.at(i)]->getCpuUsage() << std::endl
	    << std::endl;	    
	    */
	    // insert process to hash table with PID as key

      }

    pInfo = nullptr;

#if _CURSES
    // refresh the windows
    wnoutrefresh(mainWin.getWindow());
    wnoutrefresh(topWin.getWindow());
    wnoutrefresh(tasksWin.getWindow());
    wnoutrefresh(cpuWin.getWindow());
    wnoutrefresh(memWin.getWindow());
    wnoutrefresh(PIDWin.getWindow());
    wnoutrefresh(USERWin.getWindow());
    wnoutrefresh(PRWin.getWindow());
    wnoutrefresh(NIWin.getWindow());
    wnoutrefresh(VIRTWin.getWindow());
    wnoutrefresh(RESWin.getWindow());
    wnoutrefresh(SHRWin.getWindow());
    wnoutrefresh(SWin.getWindow());
    wnoutrefresh(PercentCPUWin.getWindow());
    wnoutrefresh(PercentMEMWin.getWindow());
    wnoutrefresh(TIMEWin.getWindow());
    wnoutrefresh(COMMANDWin.getWindow());
    doupdate();

    //napms(3000);
    //sleep(3);
    //delay(3000);
#endif
  }while(getch() != 'q');  

  
  endwin();
  //  for(procIt = processes.begin(); procIt != processes.end(); procIt++)

  /*
  for(auto i : processes)
    {
      log << "PID: " << i.first << std::endl;
      //    std::cout << "PID: " << i.second->setPID(5) << std::endl;
    }
  */
  
  return 0;
} // end of "main"



/*
  Function:
  printWindow

  Description:
  Prints the CursesWindow object's current data members to the log file.

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
  log << "m_maxWindowY: " << win.getMaxWindowY() << std::endl;
  log << "m_maxWindowX: " << win.getMaxWindowX() << std::endl;
  log << "m_minWindowY: " << win.getMinWindowY() << std::endl;
  log << "m_minWindowX: " << win.getMinWindowX() << std::endl;
  log << "m_centerY: " << win.getCenterY() << std::endl;
  log << "m_centerX: " << win.getCenterX() << std::endl;
  log << "m_startY: " << win.getStartY() << std::endl;
  log << "m_startX: " << win.getStartX() << std::endl;
  log << "m_currentY: " << win.getCurrentY() << std::endl;
  log << "m_currentX: " << win.getCurrentX() << std::endl;
  log << "m_previousY: " << win.getPreviousY() << std::endl;
  log << "m_previousX: " << win.getPreviousX() << std::endl;
} // end of "printWindow"
