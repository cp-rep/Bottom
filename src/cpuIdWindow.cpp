/*
  File:
   cpuIdWindow.cpp
   
  Description:
   Class implementation for the cpuIdWindow class.
*/
#include "cpuIdWindow.hpp"



/*
  Function:
   cpuIdWindow Constructor
   
  Description:
   The class constructor for creating cpuIdWindow objects and 
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
CpuIdWindow::CpuIdWindow(WINDOW* win,
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
} // end of "cpuIdWindow Constructor"
