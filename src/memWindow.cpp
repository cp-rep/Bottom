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
		     const std::string& swap) : CursesWindow(windowName,
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
} // end of "MemWindow Default Constructor"



/*
 */
void MemWindow::setStringMiB()
{
  m_MiB.clear();
} // end of "setMiB"



/*
 */
void MemWindow::setStringSwap()
{
  m_swap.clear();
} // end of "setStringSwap"


