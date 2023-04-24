/*
  File: memWindow.cpp
  Description:
 */
#include "memWindow.hpp"


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
		     const float memTotal,
		     const float memFree,
		     const float memUsed,
		     const float buffCache,
		     const float swapTotal,
		     const float swapFree,
		     const float swapUsed,
		     const float swapAvailable) : CursesWindow(windowName,
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

 */
void MemWindow::setMiB()
{
  m_MiB.append("MiB Mem: ");
  m_MiB.append(std::to_string(getMemTotal()));
  m_MiB.append(" total, ");
  m_MiB.append(std::to_string(getMemFree()));
  m_MiB.append(" free, ");
  m_MiB.append(std::to_string(getMemUsed()));
  m_MiB.append(" used. ");
  m_MiB.append(std::to_string(getBuffCache()));
  m_MiB.append(" buff/cache");
}
