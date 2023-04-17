// ============================================================================
// File: main.c
//
// Program Description:
//   A simple template for small scale C++ programs on linux based operating
//   systems.  A file logging system is provided along with a basic Foo class
//   header and source file.
// ============================================================================
#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include "numberedFile.hpp"
#include "foo.hpp"

#define DEBUG 0



// ==== main ==================================================================
//
// ============================================================================
int main()
{
  // initialize the file logging system
  NumberedFile logFile("./log/", "log", 0, ".txt");
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
      // log doens't exist, create the new log file
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
      // Output start of log session
      log << "LOG Started" << std::endl;
    }

  // local variables
  Foo myFoo(1);

  std::cout << myFoo << std::endl;
  
  return 0;
} // end of "main"
