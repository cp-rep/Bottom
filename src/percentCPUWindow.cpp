/*
  File: percentCPUWindow.cpp
  Description:
 */
#include "percentCPUWindow.hpp"

PercentCPUWindow::PercentCPUWindow(std::string windowName,	      
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

