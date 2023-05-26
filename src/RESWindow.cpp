/*
  File: RESWindow.cpp
  Description:
 */
#include "RESWindow.hpp"



RESWindow::RESWindow(WINDOW* win,
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

