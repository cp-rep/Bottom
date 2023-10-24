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
void MemWindow::setStringMiB()
{
  m_MiB.append("MiB Mem :          total,          free,          used,          buff/cache");
} // end of "setStringMiB"



/*
  Function:
   setStringSwap
  Description:

  Input:

  Output:
*/
void MemWindow::setStringSwap()
{
  m_swap = "MiB Swap:          total,          free,          used,          avail mem";
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
