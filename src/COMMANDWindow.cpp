/*
  File: 
   COMMANDWindow.cpp

  Description:
   Class implemenation for COMMANDWindow class.
 */
#include "COMMANDWindow.hpp"



/*
  Function:
   COMMANDWindow Constructor
   
  Description:
   The class constructor for creating COMMANDWindow objects and 
   initializing related calling object data.

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
   None
*/
COMMANDWindow::COMMANDWindow(WINDOW* win,
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
  fixCOMMANDWinName();
}



/*
  Function:
   fixCommandWinName

  Description:
   "Fixes" the COMMANDWindow name so it properly outputs white space appended
   to the end of the name.

  Input:
   NONE

  Output:
   m_window             - COMMANDWindow's inherited private member variable
                          window name
*/
void COMMANDWindow::fixCOMMANDWinName()
{
  std::string temp;
  int len = getNumCols() - 1;
  temp = getWindowName();
  
  for(int i = getWindowName().length() - 1; i < len; i++)
    {
      temp.push_back(' ');
    }
  
  setWindowName(temp);
} // end of "fixCOMMANDWinName"
