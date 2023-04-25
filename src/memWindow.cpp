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
		     const float& memTotal,
		     const float& memFree,
		     const float& buffers,
		     const float& cached,
		     const float& sreclaimable,
		     const float& swapTotal,
		     const float& swapFree,
		     const float& swapUsed,
		     const float& memAvailable) : CursesWindow(windowName,
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
  m_buffers = buffers;
  m_cached = cached;
  m_sreclaimable = sreclaimable;
  m_swapTotal = swapTotal;
  m_swapFree = swapFree;
  m_swapUsed = swapUsed;
  m_memAvailable = memAvailable;
} // end of "MemWindow Default Constructor"



/*
 */
const float MemWindow::convertkBToKiB(const float& val)
{
  return val * .9765625;
} // end of "convertkBToKiB"



/*
 */
const float MemWindow::convertKiBToMiB()
{
  return 0;
} // end of "convertKiBToMiB"



/*
 */
void MemWindow::setStringMiB()
{
  m_MiB.clear();
  m_MiB.append("MiB Mem: ");
  m_MiB.append(std::to_string(getMemTotal()));
  m_MiB.append(" total, ");
  m_MiB.append(std::to_string(getMemFree()));
  m_MiB.append(" free, ");
  m_MiB.append(std::to_string(getMemUsed()));
  m_MiB.append(" used. ");
  m_MiB.append(std::to_string(getBuffCache()));
  m_MiB.append(" buff/cache");
} // end of "setMiB"



/*
 */
void MemWindow::setStringSwap()
{
  m_swap.clear();
  m_swap.append("MiB Swap: ");
  m_swap.append(std::to_string(getSwapTotal()));
  m_swap.append(" total, ");
  m_swap.append(std::to_string(getSwapFree()));
  m_swap.append(" free, ");
  m_swap.append(std::to_string(getSwapUsed()));
  m_swap.append(" used. ");
  m_swap.append(std::to_string(getMemAvailable()));
  m_swap.append(" buff/cache");  
} // end of "setStringSwap"


