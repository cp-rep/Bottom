/*
  File: TIMEWindow.cpp
  Description:
 */
#include "TIMEWindow.hpp"


TIMEWindow::TIMEWindow(std::string windowName,	      
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

