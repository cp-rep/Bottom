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
 
  Potential Future Additions:
  - mouse functionality option which would then pop up a window with buttons
    to click
  - make the help menu more user friendly
  - could leverage internet connectivity.
  * pull our processes and check if any are considered melicious
  against a database.
  - could prompt chapGPT
  *same as above
  */
#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <curses.h>
#include <panel.h>
#include "log.hpp"
#include "cursesWindow.hpp"
#include <climits>

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
  Log logFile("./log/", "log", 0, ".txt");
  time_t currTime;
  struct tm* dateTime;
  std::ofstream log;

  while(true)
    {
      std::ifstream doesFileExist(logFile.getFullPath());
      
      // check if log exists      
      if(doesFileExist.is_open())
	{
	  // increment the log number and close the open file	  
	  logFile.incrementFileName();
	  doesFileExist.close();	  
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
      std::cerr << "Error creating log file. Exiting." << std::endl;
      exit(EXIT_FAILURE);
    }
  else
    {
      // output start of log session
      log << "LOG Started" << std::endl;
    }

  // local window variables
  CursesWindow processWin;
  int numLines = 0;
  int numCols = 0;
  int maxWindowY = 0;
  int maxWindowX = 0;
  int minWindowY = 0;
  int minWindowX = 0;
  int centerY = 0;
  int centerX = 0;
  int startY = 0;
  int startX = 0;
  int currentY = 0;
  int currentX = 0;
  int previousY = 0;
  int previousX = 0;
  
  
  // ## setup the main window ##
  CursesWindow mainWin;

  // init curses to main window
  mainWin.setWindow(initscr());

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
  
  // print main window to log file
  printWindowToLog(log, mainWin);  
  
  // disable echoing characters to the window from getch();
  noecho();
  
  // make typed characters immediately available to program
  // (override part of the tty driver protocol)
  cbreak();

  // disable keyboard cursor visibility
  curs_set(false);

  // disable curses defined key values for getch() to mainWin
  keypad(mainWin.getWindow(), false);

  // ## setup top window ##
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

  CursesWindow topWin("Top",
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

  // print topWin to log file
  printWindowToLog(log, topWin);

  // create the curses top window
  topWin.setWindow(newwin(topWin.getNumLines(),
			  topWin.getNumCols(),
			  topWin.getStartY(),
			  topWin.getStartX()));

  // ## setup tasks window ##
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

  CursesWindow tasksWin("Tasks",
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

  // print tasksWin to log file
  printWindowToLog(log, tasksWin);

  // create the curses task window
  tasksWin.setWindow(newwin(tasksWin.getNumLines(),
			    tasksWin.getNumCols(),
			    tasksWin.getStartY(),
			    tasksWin.getStartX()));

  // ## setup cpu window ##
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

  CursesWindow cpuWin("CPU",
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

  // print cpuWin to log file
  printWindowToLog(log, cpuWin);

  // create the curses cpu window
  cpuWin.setWindow(newwin(cpuWin.getNumLines(),
			  cpuWin.getNumCols(),
			  cpuWin.getStartY(),
			  cpuWin.getStartX()));
  
  // ## setup mem window ##
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

  CursesWindow memWin("MEM",
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

  // print topWin to log file
  printWindowToLog(log, memWin);

  // create the curses task window
  memWin.setWindow(newwin(memWin.getNumLines(),
			  memWin.getNumCols(),
			  memWin.getStartY(),
			  memWin.getStartX()));

  // ## setup PID window ##
  // define PID window
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
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

  CursesWindow PIDWin("PID",
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

  // print PIDWin to log file
  printWindowToLog(log, PIDWin);

  // create the curses top window
  PIDWin.setWindow(newwin(PIDWin.getNumLines(),
			  PIDWin.getNumCols(),
			  PIDWin.getStartY(),
			  PIDWin.getStartX()));

  // ## setup USER window ##
  // define USER window
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
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

  CursesWindow USERWin("USER",
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

  // print USERWin to log file
  printWindowToLog(log, USERWin);

  // create the curses USER window
  USERWin.setWindow(newwin(USERWin.getNumLines(),
			   USERWin.getNumCols(),
			   USERWin.getStartY(),
			   USERWin.getStartX()));

  // ## setup PR window ##
  // define PR window
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
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

  CursesWindow PRWin("PR",
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

  // print PRWin to log file
  printWindowToLog(log, PRWin);

  // create the curses PR window
  PRWin.setWindow(newwin(PRWin.getNumLines(),
			 PRWin.getNumCols(),
			 PRWin.getStartY(),
			 PRWin.getStartX()));
  
  // ## setup NI window ##
  // define NI window
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
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

  CursesWindow NIWin("NI",
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

  // print NIWin to log file
  printWindowToLog(log, NIWin);

  // create the curses NI window
  NIWin.setWindow(newwin(NIWin.getNumLines(),
			 NIWin.getNumCols(),
			 NIWin.getStartY(),
			 NIWin.getStartX()));

  // ## setup VIRT window ##
  // define VIRT window
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
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

  CursesWindow VIRTWin("VIRT",
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

  // print VIRTWin to log file
  printWindowToLog(log, VIRTWin);

  // create the curses VIRT window
  VIRTWin.setWindow(newwin(VIRTWin.getNumLines(),
			 VIRTWin.getNumCols(),
			 VIRTWin.getStartY(),
			 VIRTWin.getStartX()));

  // ## setup RES window ##
  // define RES window
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
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

  CursesWindow RESWin("RES",
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

  // print RESWin to log file
  printWindowToLog(log, RESWin);

  // create the curses RES window
  RESWin.setWindow(newwin(RESWin.getNumLines(),
			  RESWin.getNumCols(),
			  RESWin.getStartY(),
			  RESWin.getStartX()));

  // ## setup SHR window ##
  // define SHR window
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
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

  CursesWindow SHRWin("SHR",
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

  // print SHRWin to log file
  printWindowToLog(log, SHRWin);

  // create the curses SHR window
  SHRWin.setWindow(newwin(SHRWin.getNumLines(),
			  SHRWin.getNumCols(),
			  SHRWin.getStartY(),
			  SHRWin.getStartX()));

  // ## setup S window ##
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

  CursesWindow SWin("S",
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

  // print SWin to log file
  printWindowToLog(log, SWin);

  // create the curses S window
  SWin.setWindow(newwin(SWin.getNumLines(),
			SWin.getNumCols(),
			SWin.getStartY(),
			SWin.getStartX()));

  // ## setup PercentCPU window ##
  // define PercentCPU window
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
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

  CursesWindow PercentCPUWin("%CPU",
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

  // print PercentCPUWin to log file
  printWindowToLog(log, PercentCPUWin);

  // create the curses PercentCPU window
  PercentCPUWin.setWindow(newwin(PercentCPUWin.getNumLines(),
				 PercentCPUWin.getNumCols(),
				 PercentCPUWin.getStartY(),
				 PercentCPUWin.getStartX()));

  
  // ## setup PercentMEM window ##
  // define PercentMEM window
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
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

  CursesWindow PercentMEMWin("%CPU",
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

  // print PercentMEMWin to log file
  printWindowToLog(log, PercentMEMWin);

  // create the curses PercentMEM window
  PercentMEMWin.setWindow(newwin(PercentMEMWin.getNumLines(),
				 PercentMEMWin.getNumCols(),
				 PercentMEMWin.getStartY(),
				 PercentMEMWin.getStartX()));

  // ## setup TIME window ##
  // define TIME window
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
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

  CursesWindow TIMEWin("%CPU",
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

  // print TIMEWin to log file
  printWindowToLog(log, TIMEWin);

  // create the curses TIME window
  TIMEWin.setWindow(newwin(TIMEWin.getNumLines(),
			   TIMEWin.getNumCols(),
			   TIMEWin.getStartY(),
			   TIMEWin.getStartX()));

  // ## setup COMMAND window ##
  // define COMMAND window
  numLines = mainWin.getNumLines() -
             memWin.getNumLines() -
             cpuWin.getNumLines() -
             tasksWin.getNumLines() -
             topWin.getNumLines() - 1;
  //  numCols = 32767;  // max allowed value for a column initialization number
  numCols = SHRT_MAX;
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

  CursesWindow COMMANDWin("%CPU",
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

  // print COMMANDWin to log file
  printWindowToLog(log, COMMANDWin);

  // create the curses COMMAND window
  COMMANDWin.setWindow(newwin(COMMANDWin.getNumLines(),
			      COMMANDWin.getNumCols(),
			      COMMANDWin.getStartY(),
			      COMMANDWin.getStartX()));    

  // ## draw window dimension boxes and update screen buffers ##
  // draw boxes to represent window dimensions
  box(topWin.getWindow(), 'A', 'A');
  box(tasksWin.getWindow(), 'B', 'B');
  box(cpuWin.getWindow(), 'C', 'C');  
  box(memWin.getWindow(), 'D', 'D');
  box(PIDWin.getWindow(), 'E', 'E');
  box(USERWin.getWindow(), 'F', 'F');
  box(PRWin.getWindow(), 'G', 'G');    
  box(NIWin.getWindow(), 'H', 'H');
  box(VIRTWin.getWindow(), 'I', 'I');
  box(RESWin.getWindow(), 'J', 'J');
  box(SHRWin.getWindow(), 'K', 'K');
  box(SWin.getWindow(), 'L', 'L');
  box(PercentCPUWin.getWindow(), 'M', 'M');
  box(PercentMEMWin.getWindow(), 'N', 'N');  
  box(TIMEWin.getWindow(), 'O', 'O');
  box(COMMANDWin.getWindow(), 'P', 'P');  
    
  // refresh the windows to update drawn buffer to monitor
  wrefresh(mainWin.getWindow());  
  wrefresh(topWin.getWindow());
  wrefresh(tasksWin.getWindow());
  wrefresh(cpuWin.getWindow());  
  wrefresh(memWin.getWindow());
  wrefresh(PIDWin.getWindow());    
  wrefresh(USERWin.getWindow());
  wrefresh(PRWin.getWindow());    
  wrefresh(NIWin.getWindow());
  wrefresh(VIRTWin.getWindow());
  wrefresh(RESWin.getWindow());
  wrefresh(SHRWin.getWindow());        
  wrefresh(SWin.getWindow());
  wrefresh(PercentCPUWin.getWindow());
  wrefresh(PercentMEMWin.getWindow());
  wrefresh(TIMEWin.getWindow());
  wrefresh(COMMANDWin.getWindow());  

  // ## for testing ##
  if(has_colors())
    {
      use_default_colors();
      //init_pair(-1);
      //init_color(COLOR_BLACK, 0, 0, 0);
      color_set(0, NULL);
    }

  // run the main program loop
  do{
    //    wrefresh(mainWin.getWindow());
    refresh();
  }while(getch() != 'q');
  
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
