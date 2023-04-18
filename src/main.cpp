// ============================================================================
// File: main.c
//
// Program Description: A rendition of the Top program.
//
// Details:
// V0.1
//
// Potential Future Additions:
//  - could leverage internet connectivity
//    * pull our processes and check if any are considered melicious
//      against a database.
//  - could prompt chapGPT
//    * same as above
// ============================================================================
#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <curses.h>
#include <panel.h>
#include "log.hpp"
#include "foo.hpp"
#include "curseWindow.hpp"

#define DEBUG 0



// ==== main ==================================================================
//
// ============================================================================
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

  // ## initialize curses and setup main window ##
  CurseWindow mainWindow;

  // init the curses main window
  mainWindow.setWindow(initscr());

  // disable echoing characters to the window from getch();
  noecho();
  
  // make typed characters immediately available to program
  // (override part of the tty driver protocol)
  cbreak();

  // disable keyboard cursor visbiility
  curs_set(false);

  // disable curses defined key values for getch() to mainWindow
  keypad(mainWindow.getWindow(), false);
  
  while(true)
    {
      getch();
      wrefresh(mainWindow.getWindow());
    }
  
  return 0;
} // end of "main"
