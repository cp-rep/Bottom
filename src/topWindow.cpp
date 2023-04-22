/*
  File: topWindow.cpp
  Description:
*/
#include "topWindow.hpp"
#include <fstream>
#include <cstdlib>
#include <iostream>



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
  m_uptime = "";
} // end of "TopWindow Default Constructor"



/*
  Function:
  getUptime

  Description:

  Input:
  NONE
  Output:
  NONE
 */
const std::string& TopWindow::getUptime()
{
  m_uptime.clear();
  
  FILE* usersFile;
  char c = 0;

  usersFile = popen("uptime", "r");


  if(usersFile == nullptr)
    {
      perror("popen() failed to open users program.");
      exit(EXIT_FAILURE);
    }



  while(fread(&c, sizeof c, 1, usersFile))
    {
      m_uptime.push_back(c);
    }

  pclose(usersFile);

  return m_uptime;

} // end of "getUptime"



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
