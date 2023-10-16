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
- Enter "cmake -S. -B [output directory name]" to build GTest testing interface.
- Enter "cmake --build [output directory name used above]" to build test files.
- Enter "ctest" from ./Bottom/[output directory] or execute the "unit_tests" program from the ./Bottom/[output directory]/bin/unit_tests file path to start tests.

## Current Features and How to Use Them
- The arrow keys allow scrolling left right up and down shifting the windows.
- The '<' and '>' keys determine which column to sort by.
- The 'x' key allows highlighting a particular column.

## Methods
Everything has been written from scratch. I built all of the windows from running the Top program, testing it's functionality, and then coding up something that would visually represent those tests. Regarding gathering the process and OS data, that came from examining the man pages, reading from books, and researching online.  I really try to pursue the topics I am interested in the "old fashioned" way for best learning and that is what this project is.

## Why C++?
I wanted to write a small Linux process management utility that may be easier expanded upon with experimental features. I don't have much interest in actually trying to submit this into any official Linux circles or ecosystems.

## What is the state of the project?
Bottom is currently memory leak free and the "main" branch will maintain this stable version.  It currently supports Arch Linux and Ubuntu.  The tested Kernel versions will soon be tagged to corresponding commits.

## Current Challenges
Determining how to retrieve every process or OS related data piece and making subsequent calculations for correct output.

## Short Term Fixes and Changes/Additions
The following is a quick list of my most important upcoming short-term changes:
- Cleaning up ugly code
- Retrieving the few missing calculations
- Basic process management
- Adding an interruptable delay
- Unit tests

## Longer Term Changes/Additions
- Mouse functionality
- Web-based features.  For example, snap shotting the process list and uploading it to examine for unusual values that may determine a malicious connection or program.
- Potentially many others I have considered but these are at the top of my list!
