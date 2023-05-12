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
    to click. all* keyboard options should be possible with a mouse
  - make the help menu more user friendly
  - could leverage internet connectivity.
  * pull our processes and check if any are considered malicious
  against a database.
  - could prompt chapGPT
  - scan /var/log/wtmp  /var/run/utmp /var/log/btmp  for intrusions
  - adding hardware statistics to a database that we can compare to over time
    and get a "dynamic" look at how a PC performs compared to it's past.
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
#define _DEBUG 0
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
void printSortedProcsReverse(const int& startLine,
			     const std::vector<std::pair<float, int>>& sortedOut,
			     const std::unordered_map<int, ProcessInfo*>& pUmap,
			     const std::vector<CursesWindow*>& wins);
void printSortedProcs(const std::vector<int>& pidList,
		      const std::vector<std::pair<float, int>>& sortedOut,
		      const std::unordered_map<int, ProcessInfo*>& pUmap,
		      const std::vector<CursesWindow*>& wins);
void printProcs(const int& shiftY,
		const std::vector<int>& pidList,
		const std::unordered_map<int, ProcessInfo*>& pUmap,
		const std::vector<CursesWindow*>& wins);
void mergePidLists(const std::vector<std::pair<float, int>>& frontList,
		   const std::vector<int>& backList,
		   std::vector<int>& newList,
		   const std::unordered_map<int, ProcessInfo*>& pUmap);
void copyList(std::vector<int>& lhs, const std::vector<int>& rhs);
void clearBottomWins(const std::vector<CursesWindow*>& wins);
void printWindowNames(const std::vector<CursesWindow*>& wins);




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

  // vars
  std::vector<CursesWindow*> topWins;
  std::vector<CursesWindow*> bottomWins;
  MemInfo mInfo;
  ProcessInfo* pInfo;
  struct passwd* userData;
  std::vector<int> pidList;
  std::unordered_map<int, ProcessInfo*> pUmap;
  std::unordered_map<int, ProcessInfo*>::iterator pUmapIt;

  // window data vars
  CursesWindow processWin;  
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

  // swtich vars
  int stateVal = 'P';
  bool quit = false;
  int shiftY = 0;
  int shiftX = 0;
  
  // ## setup the main window ##
  CursesWindow mainWin;
  
  // init curses to main window
  mainWin.setWindow(initscr());

#if _CURSES
  if(has_colors())
    {
      use_default_colors();
      //init_pair(-1);
      //init_color(COLOR_BLACK, 0, 0, 0);
      color_set(0, NULL);
    }

  // disable echoing characters to the window from getch();
  noecho();
  
  // make typed characters immediately available to program
  // (override part of the tty driver protocol)
  cbreak();

  // disable keyboard cursor visibility
  curs_set(false);

  // disable curses defined key values for getch() to mainWin
  keypad(mainWin.getWindow(), true);

  //
  nodelay(mainWin.getWindow(), true);

  
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
  
  // store all windows in vector for polymorphic calls
  // process windows
  bottomWins.push_back(&COMMANDWin); // 0     werase(COMMANDWin.getWindow());
  bottomWins.push_back(&TIMEWin); // 1       werase(TIMEWin.getWindow());
  bottomWins.push_back(&PercentMEMWin); // 2      werase(PercentMEMWin.getWindow());
  bottomWins.push_back(&PercentCPUWin); // 3       werase(PercentCPUWin.getWindow());
  bottomWins.push_back(&SWin); // 4               werase(SWin.getWindow());
  bottomWins.push_back(&SHRWin); // 5       werase(SHRWin.getWindow());
  bottomWins.push_back(&RESWin); // 6     werase(RESWin.getWindow());    
  bottomWins.push_back(&VIRTWin); // 7       werase(VIRTWin.getWindow());
  bottomWins.push_back(&NIWin); // 8
  bottomWins.push_back(&PRWin); // 9 
  bottomWins.push_back(&USERWin); // 10
  bottomWins.push_back(&PIDWin); // 11



    werase(PIDWin.getWindow());
    werase(USERWin.getWindow());
    werase(PRWin.getWindow());
    werase(NIWin.getWindow());
    werase(SWin.getWindow());








  

  // hardware windows
  topWins.push_back(&memWin); // 0 
  topWins.push_back(&cpuWin); // 1
  topWins.push_back(&tasksWin); // 2
  topWins.push_back(&topWin); // 3

  // draw window borders
  // box(PIDWin.getWindow(), 'P', 'P');
  // box(USERWin.getWindow(), 'E', 'E');
  // box(PRWin.getWindow(), 'F', 'F');
  // box(NIWin.getWindow(), 'G', 'G');
  // box(VIRTWin.getWindow(), 'H', 'H');
  // box(RESWin.getWindow(), 'I', 'I');
  // box(SHRWin.getWindow(), 'J', 'J');
  // box(SWin.getWindow(), 'K', 'K');
  // box(PercentCPUWin.getWindow(), 'L', 'L');
  // box(PercentMEMWin.getWindow(), 'M', 'M');
  // box(TIMEWin.getWindow(), 'N', 'N');
  // box(COMMANDWin.getWindow(), 'O', 'O');
  
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
    werase(topWin.getWindow());
    werase(tasksWin.getWindow());
    werase(cpuWin.getWindow());
    werase(memWin.getWindow());
#endif
    
    // get topWin data and print to screen
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
    outLine.append(std::to_string(val));    
    if(val == 1)
      {
	outLine.append(" day, ");
      }
    else
      {
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
    
#if _CURSES
    mvwaddstr(topWin.getWindow(),
	      0,
	      0,
	      outLine.c_str());
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

    // ## find running processes and update the list if needed ##
    // store old process list
    std::vector<int> pidListOld(pidList);
    std::vector<int> pidListDead;
    std::vector<int> pidListNew;

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
	    int value = 0;
	    
	    // set pid
	    pUmap[pidList.at(i)]->setPID(pidList.at(i));
	    // log << std::endl << "PID: " << pidList.at(i) << std::endl;

	    // get command
	    filePath = currProc;
	    filePath.append(_COMM);
	    lineString = returnFileLineByNumber(filePath, 1);
	    pUmap[pidList.at(i)]->setCommand(lineString);
	    // log << "COMM: " << pUmap[pidList.at(i)]->getCommand() << std::endl;

 	    // get USER
	    filePath = currProc;
	    filePath.append(_STATUS);
	    lineString = returnPhraseLine(filePath, "Gid");
	    if(lineString != "-1")
	      {
		parsedLine = parseLine(lineString);
		value = convertToInt(parsedLine.at(1));
		userData = getpwuid(value);
		pUmap[pidList.at(i)]->setUser(userData->pw_name);
	      }
	    else
	      {
		pUmap[pidList.at(i)]->setUser("-1");
	      }


	    // get VIRT
	    lineString = returnFileLineByPhrase(filePath, "VmSize");
	    if(lineString != "-1")
	      {
		parsedLine = parseLine(lineString);
		value = convertToInt(parsedLine.at(1));
		pUmap[pidList.at(i)]->setVirt(value);
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
		float utime = 0;
		float cutime = 0;
		float pstart = 0;
		float newVal = 0;
		// get uptime
		fileLine = returnFileLineByNumber(_UPTIME, 1);
		parsedLine = parseLine(fileLine);
		newVal = convertToFloat(parsedLine.at(0));
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

		// get process %cpu
		/*
		  (utime - stime)/(system uptime - process start time)
		  (col(14) - col(15))/(/proc/uptime(0) - col(22)
		 */
 		utime = convertToInt(parsedLine.at(11));
		cutime = convertToInt(parsedLine.at(12));
		pstart = convertToInt(parsedLine.at(19));
		newVal = (utime + cutime)/(uptime.getTotalSecs() - (pstart/100));
		pUmap[pidList.at(i)]->setCPUUsage(newVal);
	      }
	    
	    // get %CPU
	    const double ticks = (double)sysconf(_SC_CLK_TCK);
	    float avgUs = 0;
	    float avgSy = 0;
	    float avgNi = 0;
	    float avgId = 0;
	    float avgWa = 0;
	    float avgHi = 0;
	    float avgSi = 0;
	    float avgSt = 0;
	    float totalJiffs = 0;
	    float us = 0;
	    float ni = 0;
	    float sy = 0;
	    float id = 0;
	    float wa = 0;
	    float irq = 0;
	    float sirq = 0;
	    float hi = 0;
	    float si = 0;
	    float st = 0;
	    float gu = 0;
	    float gun = 0;
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
	    outLine.append(std::to_string(avgUs));
	    outLine.append(" us, ");
	    outLine.append(std::to_string(avgSy));
	    outLine.append(" sy, ");
	    outLine.append(std::to_string(avgNi));
	    outLine.append(" ni, ");
	    outLine.append(std::to_string(avgId));
	    outLine.append(" id, ");
	    outLine.append(std::to_string(avgWa));
	    outLine.append(" wa, ");
	    outLine.append("N/A");
	    outLine.append(" si, ");
	    outLine.append(std::to_string(avgSt));
	    outLine.append(" st, ");

#if _CURSES
	    mvwaddstr(cpuWin.getWindow(),
		      0,
		      0,
		      outLine.c_str());
#endif	    
	    // get process state count
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
	    /*
	      log << std::endl << "PID: " << pUmap[pidList.at(i)]->getPID() << std::endl
		<< "COMM: " << pUmap[pidList.at(i)]->getCommand() << std::endl
		<< "USER: " << pUmap[pidList.at(i)]->getUser() << std::endl
		<< "PR: " << pUmap[pidList.at(i)]->getPR() << std::endl
		<< "NI: " << pUmap[pidList.at(i)]->getNI() << std::endl
		<< "VIRT: " << pUmap[pidList.at(i)]->getVirt() << std::endl
		<< "RES: " << pUmap[pidList.at(i)]->getRes() << std::endl
		<< "SHR: " << pUmap[pidList.at(i)]->getSHR() << std::endl
		<< "S: " << pUmap[pidList.at(i)]->getS() << std::endl
		<< "%CPU: " << pUmap[pidList.at(i)]->getCPUUsage() << std::endl
		<< std::endl;
	    */
      }
    
    pInfo = nullptr;
    pidListOld.clear();
    
    // ## get user input and operate on it ##
    int input;
    std::vector<std::pair<float, int>> sortedOut;
    std::vector<int> newList;
    float floatPercentage = 0;
    int intPercentage = 0;
    int oldSwitchVal;
    int moveVal = 0;

    moveVal = input = getch();
    
    if(input != -1)
      {
	if(input == 'p' ||
	   input == 'c' ||
	   input == 'q')
	  {
	    stateVal = toupper(input);
	  }
      }

    // change process state
    switch(stateVal)
      {
      case 'C':
	for(int i = 0; i < pidList.size(); i++)
	  {
	    floatPercentage = pUmap.at(pidList.at(i))->getCPUUsage();
	    floatPercentage *= 10;
	    intPercentage = floatPercentage;
	      
	    if(intPercentage != 0)
	      {
		floatPercentage = intPercentage;
		floatPercentage = floatPercentage/10;
		sortedOut.push_back(std::make_pair(floatPercentage, pidList.at(i)));
	      }
	  }
	
#if _CURSES
	mergePidLists(sortedOut,
		      pidList,
		      newList,
		      pUmap);
	clearBottomWins(bottomWins);
	printWindowNames(bottomWins);	
	printProcs(shiftY,
		   newList,
		   pUmap,
		   bottomWins);		
#endif
	break;
      case 'P':
#if _CURSES
	clearBottomWins(bottomWins);
	printWindowNames(bottomWins);
	printProcs(shiftY,
		   pidList,
		   pUmap,
		   bottomWins);	
#endif
	break;
      case 'M':
	break;
      case 'U':
	break;
      case 'Q':
	quit = true;
	break;
      default:
	break;
      }
    
    if(quit)
      {
	break;
      }


    // shift windows
    switch(moveVal)
      {
      case KEY_UP:
	shiftY++;
	log << "KEY UP!" << std::endl;
	break;
      case KEY_DOWN:
	shiftY--;	
	log << "KEY UP!" << std::endl;
      case KEY_LEFT:
	log << "KEY UP!" << std::endl;
      case KEY_RIGHT:
	log << "KEY UP!" << std::endl;	
      default:
	break;
      }
    
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
  } while(true);

  endwin();
  
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





void printSortedProcsReverse(const int& startLine,
			     const std::vector<std::pair<float, int>>& sortedOut,
			     const std::unordered_map<int, ProcessInfo*>& pUmap,
			     const std::vector<CursesWindow*>& wins)
{
  for(int k = sortedOut.size() - 1, g = startLine; k >= 0; k--, g++)
    {
      mvwaddstr(wins.at(11)->getWindow(),  // PIDWin
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getPID()).c_str());
      mvwaddstr(wins.at(10)->getWindow(), // USERWin
		g,
		0,
		pUmap.at(sortedOut.at(k).second)->getUser().c_str());
      mvwaddstr(wins.at(9)->getWindow(), // PRWin
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getPR()).c_str());
      mvwaddstr(wins.at(8)->getWindow(), // NIWin
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getNI()).c_str());
      mvwaddstr(wins.at(7)->getWindow(), // VIRTWin
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getVirt()).c_str());
      mvwaddstr(wins.at(6)->getWindow(), // RESWin
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getRes()).c_str());
      mvwaddstr(wins.at(5)->getWindow(), // SHRWin
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getSHR()).c_str());
      mvwaddch(wins.at(4)->getWindow(), // SWin
	       g,
	       0,
	       pUmap.at(sortedOut.at(k).second)->getS());
      mvwaddstr(wins.at(3)->getWindow(), // PercentCPUWin
		g,
		0,
		std::to_string(pUmap.at(sortedOut.at(k).second)->getCPUUsage()).c_str());

      mvwaddstr(wins.at(2)->getWindow(), // PercentMEMWin
		g,
		0,
		"N/A");
      mvwaddstr(wins.at(1)->getWindow(), // TIMEWin
		g,
		0,
		"N/A");
      mvwaddstr(wins.at(0)->getWindow(), // COMMANDWin
		g,
		0,
		pUmap.at(sortedOut.at(k).second)->getCommand().c_str());
    }
}



void printProcs(const int& shiftY,
		const std::vector<int>& pidList,
		const std::unordered_map<int, ProcessInfo*>& pUmap,
		const std::vector<CursesWindow*>& wins)
{
    for(int i = 0; i < pUmap.size(); i++)
    {
      int posY = i + 1 + shiftY;
      if(posY == 0)
	{
	  posY =  1;
	}

      if(pUmap.at(pidList.at(i))->getUser() == "-1")
	continue;
      
      mvwaddstr(wins.at(11)->getWindow(),
		posY,
		0,
		std::to_string(pUmap.at(pidList.at(i))->getPID()).c_str());
      mvwaddstr(wins.at(10)->getWindow(),
		posY,
		0,
		pUmap.at(pidList.at(i))->getUser().c_str());
      mvwaddstr(wins.at(9)->getWindow(),
		posY,
		0,
		std::to_string(pUmap.at(pidList.at(i))->getPR()).c_str());
      mvwaddstr(wins.at(8)->getWindow(),
		posY,
		0,
		std::to_string(pUmap.at(pidList.at(i))->getNI()).c_str());
      mvwaddstr(wins.at(7)->getWindow(),
		posY,
		0,
		std::to_string(pUmap.at(pidList.at(i))->getVirt()).c_str());
      mvwaddstr(wins.at(6)->getWindow(),
		posY,
		0,
		std::to_string(pUmap.at(pidList.at(i))->getRes()).c_str());
      mvwaddstr(wins.at(5)->getWindow(),
		posY,
		0,
		std::to_string(pUmap.at(pidList.at(i))->getSHR()).c_str());
      mvwaddch(wins.at(4)->getWindow(),
	       posY,
	       0,
	       pUmap.at(pidList.at(i))->getS());
      mvwaddstr(wins.at(3)->getWindow(),
		posY,
		0,
		std::to_string(pUmap.at(pidList.at(i))->getCPUUsage()).c_str());
      mvwaddstr(wins.at(0)->getWindow(),
		posY,
		0,
		pUmap.at(pidList.at(i))->getCommand().c_str());
    }
}


void mergePidLists(const std::vector<std::pair<float, int>>& frontList,
		   const std::vector<int>& backList,
		   std::vector<int>& newList,
		   const std::unordered_map<int, ProcessInfo*>& pUmap)
{
  // output the rest of the processes by PID in ascending order
  for(int i = 0, j = frontList.size() - 1; i < frontList.size(); i++, j--)
    {
      newList.push_back(frontList.at(j).second);
    }
  
  for(int i = 0; i < pUmap.size(); i++)
    {
      bool isInArray = false;

      for(int j = 0; j < frontList.size(); j++)
	{
	  if(frontList.at(j).second == pUmap.at(backList.at(i))->getPID())
	    {
	      isInArray = true;
	    }
	}
      if(isInArray == false)
	{
	  newList.push_back(backList.at(i));
	}
    }
}



void copyList(std::vector<int>& lhs, const std::vector<int>& rhs)
{
  for(int i = 0; i < rhs.size(); i++)
    {
      lhs.push_back(rhs.at(i));
    }
}




void printWindowNames(const std::vector<CursesWindow*>& wins)
{
  mvwaddstr(wins.at(11)->getWindow(),
	      0,
	      0,
	      wins.at(11)->getWindowName().c_str());
    mvwaddstr(wins.at(10)->getWindow(),
	      0,
	      0,
	      wins.at(10)->getWindowName().c_str());
    mvwaddstr(wins.at(9)->getWindow(),
	      0,
	      0,
	      wins.at(9)->getWindowName().c_str());
    mvwaddstr(wins.at(8)->getWindow(),
	      0,
	      0,
	      wins.at(8)->getWindowName().c_str());
    mvwaddstr(wins.at(7)->getWindow(),
	      0,
	      0,
	      wins.at(7)->getWindowName().c_str());
    mvwaddstr(wins.at(6)->getWindow(),
	      0,
	      0,
	      wins.at(6)->getWindowName().c_str());
    mvwaddstr(wins.at(5)->getWindow(),
	      0,
	      0,
	      wins.at(5)->getWindowName().c_str());
    mvwaddstr(wins.at(4)->getWindow(),
	      0,
	      0,
	      wins.at(4)->getWindowName().c_str());
    mvwaddstr(wins.at(3)->getWindow(),
	      0,
	      0,
	      wins.at(3)->getWindowName().c_str());
    mvwaddstr(wins.at(2)->getWindow(),
	      0,
	      0,
	      wins.at(2)->getWindowName().c_str());
    mvwaddstr(wins.at(1)->getWindow(),
	      0,
	      0,
	      wins.at(1)->getWindowName().c_str());
    mvwaddstr(wins.at(0)->getWindow(),
	      0,
	      0,
	      wins.at(0)->getWindowName().c_str());  
}




void clearBottomWins(const std::vector<CursesWindow*>& wins)
{
    werase(wins.at(11)->getWindow());
    werase(wins.at(10)->getWindow());
    werase(wins.at(9)->getWindow());
    werase(wins.at(8)->getWindow());
    werase(wins.at(7)->getWindow());
    werase(wins.at(6)->getWindow());    
    werase(wins.at(5)->getWindow());
    werase(wins.at(4)->getWindow());
    werase(wins.at(3)->getWindow());
    werase(wins.at(2)->getWindow());
    werase(wins.at(1)->getWindow());
    werase(wins.at(0)->getWindow());  
}
