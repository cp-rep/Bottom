/*
  File: PRWindow.cpp
  Description:
 */
#include "PRWindow.hpp"


PRWindow::PRWindow(std::string windowName,	      
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
