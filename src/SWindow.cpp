/*
  File: SWindow.cpp
  Description:
 */
#include "SWindow.hpp"


SWindow::SWindow(WINDOW* win,
		 const std::string windowName,	      
		 const short& numLines,
		 const short& numCols,
		 const short& startY,
		 const short& startX) : CursesWindow(win,
						     windowName,
						     numLines,
						     numCols,
						     startY,
						     startX)
{
}

