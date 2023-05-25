/*
  File: COMMANDWindow.cpp
  Description:
 */
#include "COMMANDWindow.hpp"



COMMANDWindow::COMMANDWindow(std::string windowName,	      
			     const short& numLines,
			     const short& numCols,
			     const short& startY,
			     const short& startX) : CursesWindow(windowName,
								 numLines,
								 numCols,
								 startY,
								 startX)
{
  fixCOMMANDWinName();
}



/*
  Function:
  fixCommandWinName

  Description:

  Input:

  Output:
 
 */
void COMMANDWindow::fixCOMMANDWinName()
{
  std::string temp;
  int len = getNumCols() - getWindowName().length();
  temp = getWindowName();
  
  for(int i = getWindowName().length(); i < len; i++)
    {
      temp.push_back(' ');
    }
  
  setWindowName(temp);
} // end of "fixCOMMANDWinName"
