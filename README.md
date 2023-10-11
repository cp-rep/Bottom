# Bottom

## What is this project?
The Bottom program is an exploration in Linux and NCurses through recreating Top from the GNU Core Utilities using C++.

## Methods
Everything has been written from scratch, done by eye, and from testing the Top program.  I have not examined the C code for either the GNU Core Utilities Top program or the HTop code.  I have used the man pages for the Top program and other built-in programs such as "user", "ls" to help explain where those programs pull their process/OS data from.

## Why in the world did I use C++?
Yes, I know it is complete blasphemy to use C++ for a Linux program and that Linus Torvalds would never accept this in any Linux echo system ever.  However, that is one of the very reasons I wanted to write this program in C++.  I wanted to write a Linux process management utility that may be easier expanded upon with experimental features.  As it currently sits, it is comparatively lightweight to the C implementation of Top.

## What is the state of the project?
Bottom is currently memory leak free and displays 90% of Top's data from the default screen.  The "main" branch will maintain this stable version.  It currently supports Arch Linux and Ubuntu.  The tested Kernel versions will soon be tagged to the corresponding pushes.

## What are the current challenges?
I have not determined how to calculate every single process related or OS related data piece and researching those calculations has proved very time consuming.  I would estimate that the research has often taken as much time as the coding. In consequence, I'm using at least one core utility program piped from a function call to retrieve that calculation.  This results in the main program loop infinitely expanding it's total process count (even though the process closes correctly the total PID number grows very quickly).

## What short term fixes/changes should the project see?
The following is a quick list of my most important upcoming short-term changes:
- Cleaning up the very ugly code
- Adding an interruptable delay
- Removing any useless/deprecated functions
- Writing proper comments for function implementations
- Creating appropriate files for related functions
- Making main more readable
- Improving DRY
- Adding unit tests for appropriate functions in GTEST

## What long term changes?
- Most if not all of the functionality that Top offers
- Mouse functionality
- Web-based features.  For example, snap shotting the process list and uploading it to examine for unusual values that may determine a malicious connection or program.
- Potentially many others I have considered but these are at the top of my list!
