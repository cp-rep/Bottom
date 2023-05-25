/*
  File: PIDWindow.cpp
  Description:
 */
#include "PIDWindow.hpp"



PIDWindow::PIDWindow(std::string windowName,	      
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

