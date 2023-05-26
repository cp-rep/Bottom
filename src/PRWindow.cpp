/*
  File: PRWindow.cpp
  Description:
 */
#include "PRWindow.hpp"


PRWindow::PRWindow(WINDOW* win,
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
