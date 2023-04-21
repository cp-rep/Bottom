/*
  File: cpuWindow.cpp
  Description:
 */
#include "cpuWindow.hpp"



CpuWindow::CpuWindow(std::string windowName,	      
		     const short& numLines,
		     const short& numCols,
		     const short& maxWindowY,
		     const short& maxWindowX,
		     const short& minWindowY,
		     const short& minWindowX,
		     const short& centerY,
		     const short& centerX,
		     const short& startY,
		     const short& startX,
		     const short& currentY,
		     const short& currentX,
		     const short& previousY,
		     const short& previousX) : CursesWindow(windowName,
							    numLines,
							    numCols,
							    maxWindowY,
							    maxWindowX,
							    minWindowY,
							    minWindowX,
							    centerY,
							    centerX,
							    startY,
							    startX,
							    currentY,
							    currentX,
							    previousY,
							    previousX)
{
}
