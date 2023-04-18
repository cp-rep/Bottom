// ============================================================================
// File: main.c
//
// Program Description: A recreation of the Top program.
//
// Details:
// V0.1
//
// ============================================================================
#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <curses.h>
#include <panel.h>
#include "log.hpp"
#include "foo.hpp"
#include "curseWindows.hpp"

#define DEBUG 0



// ==== main ==================================================================
//
// ============================================================================
int main()
{
  // initialize the file logging system
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

  // begin curses initiliazation
  
  

  
  
  return 0;
} // end of "main"
