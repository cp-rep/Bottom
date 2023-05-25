/*
  File: SHRWindow.cpp
  Description:
 */
#include "SHRWindow.hpp"



SHRWindow::SHRWindow(std::string windowName,	      
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

