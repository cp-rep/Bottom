/*
  File: RESWindow.cpp
  Description:
 */
#include "RESWindow.hpp"



RESWindow::RESWindow(std::string windowName,	      
		     const short& numLines,
		     const short& numCols,
		     const short& startY,
		     const short& startX) : CursesWindow(windowName,
							 numLines,
							 numCols,
							 startY,
							 startX)
{
}

