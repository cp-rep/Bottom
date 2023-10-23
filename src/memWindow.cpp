/*
  File: memWindow.cpp
  Description:
*/
#include "memWindow.hpp"



/*
  Function:
   MemWindow Constructor

  Description:
   The class constructor for creating MemWindow objects and 
   initializing related object data.

  Input:
   win                  - a pointer to a NCurses window that contains the 
                          address to the newly created Window.

   windowName           - a const reference to the name to be stored in
                          Window's private member variable m_window.

   numLines             - a const int reference to the max number of lines of the
                          created Window.

   numCols              - a const int reference to the max number of columns of
                          the created Window.
 
   startY               - a const int reference that defines the logical starting
                          line number of the Window.

   startX               - a const int reference that defines the logical starting
                          column number of the Window.
  Output:
   NONE
*/
MemWindow::MemWindow(WINDOW* win,
		     const std::string& windowName,	      
		     const short& numLines,
		     const short& numCols,
		     const short& startY,
		     const short& startX) : CursesWindow(win,
							 windowName,
							 numLines,
							 numCols,
							 startY,
							 startX)
{
} // end of "MemWindow Constructor"



/*
  Function:
   setStringMiB

  Description:

  Input:

  Output:
*/
void MemWindow::setStringMiB(const std::string& memTotal,
			     const std::string& memFree,
			     const std::string& memUsed,
			     const std::string& buffCache)
{
  m_MiB.clear();
  m_MiB.append("MiB Mem: ");
  m_MiB.append(memTotal);
  m_MiB.append(" total, ");
  m_MiB.append(memFree);
  m_MiB.append(" free, ");
  m_MiB.append(memUsed);
  m_MiB.append(" used, ");
  m_MiB.append(buffCache);
  m_MiB.append(" buff/cache");
} // end of "setStringMiB"



/*
  Function:
   setStringSwap
  Description:

  Input:

  Output:
*/
void MemWindow::setStringSwap(const std::string& swapTotal,
			      const std::string& swapFree,
			      const std::string& swapUsed,
			      const std::string& memAvailable)
{
  m_swap.clear();
  m_swap.append("MiB Swap: ");
  m_swap.append(swapTotal);
  m_swap.append(" total, ");
  m_swap.append(swapFree);
  m_swap.append(" free, ");
  m_swap.append(swapUsed);
  m_swap.append(" used, ");
  m_swap.append(memAvailable);
  m_swap.append(" avail/mem");
} // end of "setStringSwap"



/*
  Function:
   getMiB

  Description:

  Input:

  Output:
*/
const std::string& MemWindow::getMiB() const
{
  return m_MiB;
} // end of "getMiB"



/*
  Function:
   getSwap
  Description:

  Input:

  Output:
*/
const std::string& MemWindow::getSwap() const
{
  return m_swap;
} // end of "getSwap"
