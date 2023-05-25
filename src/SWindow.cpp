/*
  File: SWindow.cpp
  Description:
 */
#include "SWindow.hpp"


SWindow::SWindow(std::string windowName,	      
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

