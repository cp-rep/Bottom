# Bottom

## What is Bottom?
The Bottom program is an exploration in Linux and NCurses through creating a Top-like program from the GNU Core Utilities using C++.  It is not meant to be Top but a side project for learning and experimental features.

## How to Build Bottom
Bottom uses the "CMake" utility for building the base program.
- Enter "make dirs" while in Bottom's working directory to build the "bin" and "log" directories.
- Enter "make" while in Bottom's working directory to build.
- Enter "make clean" to clean up build files.

## Current Features and How to Use Them
- The arrow keys allow scrolling left right up and down shifting the windows.
- The '<' and '>' keys determine which column to sort by.
- The 'x' key allows highlighting a particular column (currently a "smear" bug when hightlighting and shifting).

## Methods
Everything has been written from scratch. I built all of the windows from running the Top program, testing it's functionality, and then coding up something that would visually represent those tests. Regarding gathering the process and OS data, that came from examining the man pages, reading from books, and researching online.  I really try to pursue the topics I am interested in the "old fashioned" way for best learning and that is what this project is.

## Why C++?
I wanted to write a small Linux process management utility that may be easier expanded upon with experimental features. I don't have much interest in actually trying to submit this into any official Linux circles or ecosystems.

## What is the state of the project?
Bottom is currently memory leak free and the "main" branch will maintain this stable version.  It currently supports Arch Linux and Ubuntu.  The tested Kernel versions will soon be tagged to corresponding commits.

## Current Challenges
I have not determined how to calculate every single process related or OS related data piece and researching those calculations has proved very time consuming.  I would estimate that the research has often taken as much time as the coding. In consequence, I'm using at least one core utility program piped from a function call to retrieve that calculation.  This results in the main program loop infinitely expanding it's total process count (even though the process closes correctly the total PID number grows very quickly).

## Short Term Fixes and Changes/Additions
The following is a quick list of my most important upcoming short-term changes:
- Cleaning up ugly code
- Basic process management
- Adding an interruptable delay
- Removing any useless/deprecated functions
- Unit tests

## Longer Term Changes/Additions
- Mouse functionality
- Web-based features.  For example, snap shotting the process list and uploading it to examine for unusual values that may determine a malicious connection or program.
- Potentially many others I have considered but these are at the top of my list!
