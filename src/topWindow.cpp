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
  maxWindowY      -
  maxWindowX      -
  minWindowY      -
  minWindowX      -
  centerY         -
  centerX         -
  startY          -
  startX          -
  currentY        -
  currentX        -
  previousY       -
  previousX       -

  Output:
  NONE
*/
TopWindow::TopWindow(std::string windowName,	      
		     const short& numLines,
		     const short& numCols,
		     const short& maxWindowY,
		     const short& maxWindowX,
		     const short& minWindowY,
		     const short& minWindowX,
		     const short& centerY,
		     const short& centerX,
		     const short& startY,
		     const short& startX,
		     const short& currentY,
		     const short& currentX,
		     const short& previousY,
		     const short& previousX) : CursesWindow(windowName,
							    numLines,
							    numCols,
							    maxWindowY,
							    maxWindowX,
							    minWindowY,
							    minWindowX,
							    centerY,
							    centerX,
							    startY,
							    startX,
							    currentY,
							    currentX,
							    previousY,
							    previousX)
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
