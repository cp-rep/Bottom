/*
  File: NIWindow.cpp
  Description:
 */
#include "NIWindow.hpp"


NIWindow::NIWindow(std::string windowName,	      
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

