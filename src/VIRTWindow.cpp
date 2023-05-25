/*
  File: VIRTWindow.cpp
  Description:
 */
#include "VIRTWindow.hpp"



VIRTWindow::VIRTWindow(std::string windowName,	      
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
