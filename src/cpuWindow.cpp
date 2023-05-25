/*
  File: cpuWindow.cpp
  Description:
 */
#include "cpuWindow.hpp"


CpuWindow::CpuWindow(std::string windowName,	      
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

