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
- The arrow keys allow shifting the windows left, right, up, and down.
- The '<' and '>' keys determine which column to sort by.
- The 'x' key allows highlighting a particular column.

## Why C++?
I wanted to write a small Linux process management utility that may be easier expanded upon with experimental features. I don't have much interest in actually trying to submit this into any official Linux circles or ecosystems.

## What is the state of the project?
The main branch will maintain the stable version of Bottom.  It currently supports Arch Linux and Ubuntu which are the operating systems it has been tested on.  However, most Linux distributions should work just fine.

## Current Challenges/Known Issues
Some information does not match one to one to Top.  One such example are the CPU User Time and System Time averages and related values.  These need to be measured over a duration to get the correct average usage rates.  These calculations will eventually be rectified in the threaded branch down the line.  Another example is the number of users logged into the system which are not correct and currently set to 0.  All Research has pointed towards that data being retrieved from the '/var/run/utmp' file which requires a UTMP dump or some other method to interface with it such as non-standard libraries like 'libutempter'.

## Short Term Fixes and Changes/Additions
The following is a quick list of my most important upcoming short-term changes:
- Basic process management
- Adding an interruptable delay
- Unit tests

## Longer Term Changes/Additions
- Mouse functionality
- Web-based features.  For example, snap shotting the process list and uploading it to examine for unusual values that may determine a malicious connection or program.
- Potentially many others I have considered but these are at the top of my list!
