/*
  File: percentMEMWindow.cpp
  Description:
 */
#include "percentMEMWindow.hpp"


PercentMEMWindow::PercentMEMWindow(std::string windowName,	      
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
