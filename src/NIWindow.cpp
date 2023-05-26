/*
  File: NIWindow.cpp
  Description:
 */
#include "NIWindow.hpp"


NIWindow::NIWindow(WINDOW* win,
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

