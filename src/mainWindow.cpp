/*
  File: mainWindow.cpp
  Description:
 */
#include "mainWindow.hpp"

MainWindow::MainWindow(WINDOW* win,
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


