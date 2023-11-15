/*
  File: 
   cursesWindow.cpp
 
  Description: 
   The implementation of the CursesWindow.hpp class.
*/
#include "cursesWindow.hpp"



/*
  Function:
   CursesWindow Constructor
   
  Description:
   The base class constructor for creating CursesWindow objects and 
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
CursesWindow::CursesWindow(WINDOW* win,
			   const std::string& windowName,
			   const int& numLines,
			   const int& numCols,
			   const int& startY,
			   const int& startX)
{
  defineWindow(win,
	       windowName,
	       numLines,
	       numCols,
	       startY,
	       startX);
} // end of "CursesWindow Constructor"



/*
  Function:
   CursesWindow Destructor
   
  Description:
   Frees the window corresponding to the calling object from memory.

  Input:
   NONE
  
  Output:
   NONE
*/
CursesWindow::~CursesWindow()
{
  if(getWindow() != nullptr)
    {
      deleteWindow();
    }
} // end of "CursesWindow Destructor"



/*
  Function:
   defineWindow
   
  Description:
   Defines the calling object's private member window data.

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
void CursesWindow::defineWindow(WINDOW* win,
				const std::string& windowName,
				const int& numLines,
				const int& numCols,
				const int& startY,
				const int& startX)
{
  m_window = win;
  m_windowName = windowName;
  m_numLines = numLines;
  m_numCols = numCols;
  m_startY = startY;
  m_startX = startX;
} // end of "defineWindow"




/*
  Function:
   createWindow
   
  Description:
   Creates a new window and stores it's address in the calling object's
   private member data.

  Input:
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
void CursesWindow::createWindow(const int& numLines,
				const int& numCols,
				const int& startY,
				const int& startX)
{
  if(m_window == nullptr)
    {
      m_window = newwin(numLines,
			numCols,
			startY,
			startX);
    }
  else
    {
      endwin();
      exit(EXIT_FAILURE);
    }
} // end of "createWindow"



/*
  Function:
   getWindow

  Description:
   Returns a pointer to the calling object's corresponding window.

  Input:
   NONE

  Output:
   WINDOW*              - a pointer to the calling object's window.
*/
WINDOW* CursesWindow::getWindow()
{
  return m_window;
} // end of "getWindow"



/*
  Function:

  Description:
*/
const std::string& CursesWindow::getWindowName() const
{
  return m_windowName;
} // end of "getWindowName"



/*
  Function:
   getNumLines

  Description:
   Returns the max number of lines corresponding to the calling object's
   window.

  Input:
   NONE

  Output:
   const int&           - a const int reference to the calling object's private
                          data member for the max number of lines for its window.
*/
const int& CursesWindow::getNumLines() const
{
  return m_numLines;
} // end of "getNumLines"



/*
  Function:
   getNumCols

  Description:
   Returns the max number of columns corresponding to the calling object's
   window.

  Input:
   NONE

  Output:
   const int&           - a const int reference to the calling objects private
                          data member for the max number of columns for its window.  
*/
const int& CursesWindow::getNumCols() const
{
  return m_numCols;
} // end of "getNumCols"


/*
  Function:
   getStartY

  Description:
   Returns the value representing the logical starting line number of the calling
   object's window.
 
  Input:
   NONE
  
  Output:
   const int&           - a const int reference to the calling objects logical 
                          starting line number.
*/
const int& CursesWindow::getStartY() const
{
  return m_startY;
} // end  of "getStartY"



/*
  Function:
   getStartX

  Description:
   Returns the value representing the logical starting column number of the calling
   object's window.

  Input:
   NONE
  
  Output:
   const int&           - a const int reference to the calling object's logical 
                          starting line number.   
*/
const int& CursesWindow::getStartX() const
{
  return m_startX;
} // end of "getStartX"



/*
  Function:
   setWindow

  Description:
   Stores the address of the incoming WINDOW* into the private WINDOW* data member
   of the calling object.

  Input:
   window               - The address of an incoming WINDOW.

  Output:
   NONE
*/
void CursesWindow::setWindow(WINDOW* window)
{
  m_window = window;
} // end of "setWindow"



/*
  Function:
   setWindowName

  Description:
   Defines the private member data for the calling object's window name.
  
  Input:
   winName              - a const string representing the window name to be
                          stored for the calling object's window name.

  Output:
   NONE
*/
void CursesWindow::setWindowName(const std::string& winName)
{
  m_windowName = winName;
} // end of "setWindowName"



/*
  Function:
   setNumLines

  Description:
   Defines the private member data for the calling object's max number of lines for
   its window.

  Input:
   numLines             - a const int reference for the maximum number of lines for
                          the calling object's window.

  Output:
   NONE
*/
void CursesWindow::setNumLines(const int& numLines)
{
  m_numLines = numLines;
} // end of "setNumLines"



/*
  Function:

  Description:
   Defines the private member data for the calling object's max number of columns 
   for its window.

  Input:
   numLines             - a const int reference for the maximum number of columns 
                          for the calling object's window.
  Output:
   NONE
*/
void CursesWindow::setNumCols(const int& numCols)
{
  m_numCols = numCols;
} // end of "setNumCols"



/*
  Function:
   setStartY

  Description:
   Defines the private member data for the calling object's logical starting
   line of the window.
   
  Input:
   startY               - a const int reference that defines the logical starting
                          line number of the Window.
  Output:
   NONE
*/
void CursesWindow::setStartY(const int& startY)
{
  m_startY = startY;
} // end of "setStartY"



/*
  Function:
   setStartX

  Description:
   Defines the private member data for the calling object's logical starting
   column of the window.
   
  Input:
   startY               - a const int reference that defines the logical starting
                          column number of the Window.
  Output:
   NONE
*/
void CursesWindow::setStartX(const int& startX)
{
  m_startX = startX;
} // end of "setStartX"



/*
  Function:
   deleteWindow

  Description:
   Frees the calling object's window from memory.
  
  Input:
   NONE

  Output:
   NONE
*/
void CursesWindow::deleteWindow()
{
  delwin(getWindow());
  setWindow(nullptr);
} // end of "deleteWindow"
