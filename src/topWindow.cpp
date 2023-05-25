/*
  File: topWindow.cpp
  Description:
*/
#include "topWindow.hpp"



/*
  Function:
  TopWindow Default Constructor
   
  Description:

  Input:
  windowName      -
  numLines        -
  numCols         -
  startY          -
  startX          -

  Output:
  NONE
*/
TopWindow::TopWindow(std::string windowName,	      
		     const short& numLines,
		     const short& numCols,
		     const short& startY,
		     const short& startX) : CursesWindow(windowName,
							 numLines,
							 numCols,
							 startY,
							 startX)
{
  m_uptime = "";
} // end of "TopWindow Default Constructor"



/*
  Function:
  getUptime

  Description:
  Returns the m_uptime member variable.

  Input:
  NONE

  Output:
  m_uptime               - a const reference to the m_uptime
                           member variable.
*/
const std::string& TopWindow::getUptime()
{
  return m_uptime;
} // end of "getUptime"



/*
  Function:
  setUptime

  Description:
  Clears and sets the m_uptime member variable making it
  "display ready" for output to the screen in Top program
  format.

  Input:
  NONE

  Output:
  NONE
*/
void TopWindow::setUptime(const std::string& uptime)
{
  m_uptime.clear();
  m_uptime.append("top -");
  m_uptime.append(uptime);
} // end of "setUptime"
