/*
  File: SHRWindow.cpp
  Description:
 */
#include "SHRWindow.hpp"



SHRWindow::SHRWindow(WINDOW* win,
		     std::string windowName,	      
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

