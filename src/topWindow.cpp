/*
  File: topWindow.cpp
  Description:
*/
#include "topWindow.hpp"
#include <fstream>


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
		     const short& previousX,
		     struct tm* timeinfo) : CursesWindow(windowName,
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
  m_time = "";
  m_uptime = "";
  m_users = "";
  m_loadAverage = "";
} // end of "TopWindow Default Constructor"



/*
  Function:
  getTime

  Description:

  Input:
  NONE
  Output:
  NONE
 */
const std::string& TopWindow::getTime() const
{
  return m_time;
} // end of "getTime"



/*
  Function:
  getUptime

  Description:

  Input:
  NONE
  Output:
  NONE
 */
const std::string& TopWindow::getUptime() const
{
  return m_uptime;
} // end of "getUptime"



/*
  Function:
  setTime

  Description:

  Input:
  NONE
  Output:
  NONE
 */
void TopWindow::setTime(struct tm* timeinfo)
{
  m_time.clear();
  m_time.append(std::to_string(timeinfo->tm_hour));
  m_time.append(":");
  m_time.append(std::to_string(timeinfo->tm_min));
  m_time.append(":");
  m_time.append(std::to_string(timeinfo->tm_sec));
} // end of "setTime"



/*
  Function:
  setUptimeFromFile

  Description:

  Input:
  NONE
  Output:
  NONE
 */
void TopWindow::setUptimeFromFile()
{
  std::ifstream inFile;
  inFile.open("/proc/uptime", std::ifstream::in);

  if(!inFile.is_open())
    {
      return;
    }
  
  double quotient;
  short hours;
  short minutes;

  inFile >> quotient;
  quotient = (quotient/60);
  quotient = quotient/60;
  hours = quotient;
  quotient = quotient - hours;
  minutes = quotient * 60;

  m_uptime.append(std::to_string(hours));
  m_uptime.append(":");
  m_uptime.append(std::to_string(minutes));
} // end of "setUptimeFromFile"



/*
  Function:
  drawTop

  Description:

  Input:
  NONE
  Output:
  NONE
 */
void TopWindow::drawTop()
{
} // end of "getSeconds"
