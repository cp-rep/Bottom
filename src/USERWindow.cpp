/*
  File: USERWindow.cpp
  Description:
 */
#include "USERWindow.hpp"



USERWindow::USERWindow(std::string windowName,	      
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
