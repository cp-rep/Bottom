/*
  File:
   cpuHiWindow.cpp
   
  Description:
   Class implementation for the CpuHiWindow class.
*/
#include "cpuHiWindow.hpp"



/*
  Function:
   CpuHiWindow Constructor
   
  Description:
   The class constructor for creating CpuHiWindow objects and 
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
CpuHiWindow::CpuHiWindow(WINDOW* win,
		       const std::string windowName,	      
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
} // end of "CpuHiWindow Constructor"
