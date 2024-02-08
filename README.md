# Bottom

## What is Bottom?
The Bottom program is an exploration in Linux and NCurses through creating a Top-like program from the GNU Core Utilities using C++.  It is not meant to be Top but a side project for learning and experimental features.

## How to Build Bottom
Bottom uses the Make utility for building the base program. Use all commands from the ./Bottom working directory.
- Enter "make dirs" to create necessary directories.
- Enter "make" to build the program.
- Enter "make clean" to remove all build files.

## How to Build Unit Tests
Bottom uses GTest for its unit testing.  GTest requires the GTest package and uses the CMake utility and Python3 for building GTest files and directories. Use all commands from the ./Bottom working directory unless directed otherwise.
- Enter "cmake -S . -B [output directory name]" to build GTest testing interface.
- Enter "cmake --build [output directory name used above]" to build test files.
- Enter command "./[output directory]/bin/unit_tests" from the ./Bottom base directory.  Some tests will fail due to file reading if not executed from the ./Bottom directory.

## Current Features and How to Use Them
- The 'h' key enters the help menu with all current features.
- The arrow keys allow shifting the windows left, right, up, and down.
- The '<' and '>' keys determine which column to sort by.
- The 'x' key allows highlighting a particular column.
- The 'k' key allows the user to "kill" desired processes.
- The 'c' key opens, resizes, or closes the cpu utilization window.
- The 'm' key opens, resizes, or closes the main memory usage window.

## Why C++?
I wanted to write a small Linux process management utility that may be easier expanded upon with experimental features. I don't have much interest in actually trying to submit this into any official Linux circles or ecosystems.

## What is the state of the project?
The main branch will maintain the stable version of Bottom.  It currently supports Arch Linux and Ubuntu which are the operating systems it has been tested on.  However, most Linux distributions should work just fine.

## Current Challenges/Known Issues
- The current number of users are not gathered the same as Top.  According to the man pages for Top, Top gathers its data from '/var/run/utmp'.  Unfortunately, this file varies between platforms having been confirmed developing this program on both Arch Linux and Ubuntu. I have considered writing platform specific code to read from it, however, I have discovered in testing that Top reports the number of current users differently between these Linux distributions and others. Therefore I have chosen to report the number of users in Bottom based upon the different user strings reported in the "USER" column for process data.
- Sychronizing an interruptable delay for the multithreaded version of Bottom has not yet been implemented. This is one of the features I am currently working on.

## Future Changes/Additions I Would Like to Implement
- Improved multithreading.
- Other standard OS tool features.
- Potentially others.
