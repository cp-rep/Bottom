/*
  File: memWindow.cpp
  Description:
 */
#include "memWindow.hpp"
#include <fstream>
#include <cstdlib>


/*
  Function:
  MemWindow Default Constructor
   
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
MemWindow::MemWindow(std::string windowName,	      
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
		     const std::string& MiB,
		     const std::string& swap,
		     const int memTotal,
		     const int memFree,
		     const int memUsed,
		     const int buffCache,
		     const int swapTotal,
		     const int swapFree,
		     const int swapUsed,
		     const int swapAvailable) : CursesWindow(windowName,
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
  m_MiB = MiB;
  m_swap = swap;
  m_memTotal = memTotal;
  m_memFree = memFree;
  m_memUsed = memUsed;
  m_buffCache = buffCache;
  m_swapTotal = swapTotal;
  m_swapFree = swapFree;
  m_swapUsed = swapUsed;
  m_swapAvailable = swapAvailable;
} // end of "MemWindow Default Constructor"




/*
  Function:
  readMiBTotal
   
  Description:

  Input:
  NONE
  
  Output:
  NONE
*/
const std::string MemWindow::readMiBTotal()
{
  std::string temp;
  std::ifstream inFile("/proc/meminfo", std::ifstream::in);
  std::getline(inFile, temp);
  inFile.close();
  return temp;
} // end of "readMiBTotal"
