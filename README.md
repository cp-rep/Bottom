# Bottom

## What is this project?
The Bottom program is an exploration in Linux and NCurses through recreating Top from the GNU Core Utilities using C++.

## How to Build Bottom
Bottom uses the "CMake" utility for building the base program.
- Type "make" while in Bottom's working directory to build.
- Type "make clean" to clean up build files.

## Current Features and How to Use Them
- the arrow keys allow scrolling left right up and down shifting the windows
- the '<' and '>' keys determine which column to sort by
- the 'x' key allows highlighting a particular column (currently a "smear" bug when hightlighting and shifting)

## Methods
Everything has been written from scratch. I built all of the windows from running the Top program, testing it's functionality, and then returning to code up what I felt it was doing. Regarding gathering the process and OS data, that came from examining the man pages, reading from books, and researching online.  I really try to pursue the topics I am interested in the "old fashioned" way for best learning and that is what this project is.

## Why C++?
I wanted to write a Linux process management utility that may be easier expanded upon with experimental features. I don't have much interest in actually trying to submit this into any official Linux circles or ecosystems.

## What is the state of the project?
Bottom is currently memory leak free and displays 90% of Top's data from the default screen.  The "main" branch will maintain this stable version.  It currently supports Arch Linux and Ubuntu.  The tested Kernel versions will soon be tagged to corresponding commits.

## Current Challenges
I have not determined how to calculate every single process related or OS related data piece and researching those calculations has proved very time consuming.  I would estimate that the research has often taken as much time as the coding. In consequence, I'm using at least one core utility program piped from a function call to retrieve that calculation.  This results in the main program loop infinitely expanding it's total process count (even though the process closes correctly the total PID number grows very quickly).

## Short Term Fixes and Changes/Additions
The following is a quick list of my most important upcoming short-term changes:
- Cleaning up the very ugly code
- A bash or python script to check for all proper directory files/folders for build
- Adding an interruptable delay
- Removing any useless/deprecated functions
- Writing proper comments for function implementations
- Creating appropriate files for related functions
- Making main more readable
- Improving DRY
- Adding unit tests for appropriate functions in GTEST

## Long Term Changes/Additions
- Most if not all of the functionality that Top offers
- Mouse functionality
- Web-based features.  For example, snap shotting the process list and uploading it to examine for unusual values that may determine a malicious connection or program.
- Potentially many others I have considered but these are at the top of my list!
