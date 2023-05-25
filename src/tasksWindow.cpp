/*
  File: tasksWindow.cpp
  Description:
 */
#include "tasksWindow.hpp"


TasksWindow::TasksWindow(std::string windowName,	      
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


