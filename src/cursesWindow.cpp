/*
  File: cursesWindow.cpp
 
  Description: The implementation of the CursesWindow class.
*/
#include "cursesWindow.hpp"



/*
  Function:
  CursesWindow Default Constructor
   
  Description:
  Initializes the main screen of the Top program.

  Input:
  windowName      -
  numLines        -
  numCols         -
  startY          -
  startX          -
  
  Output:
  None
*/
CursesWindow::CursesWindow(std::string windowName,
			   const int& numLines,
			   const int& numCols,
			   const int& startY,
			   const int& startX)
{
  defineWindow(windowName,
	       numLines,
	       numCols,
	       startY,
	       startX);
} // end of "CursesWindow Default Constructor"



/*
  Function:
  Destructor
   
  Description:

  Input:
  
  Output:

*/
CursesWindow::~CursesWindow()
{
  if(getWindow() != nullptr)
    {
      deleteWindow();
    }
} // end of "Destructor"



/*
  Function:
   defineWindow
   
  Description:

  Input:
  
  Output:

*/
void CursesWindow::defineWindow(std::string windowName,
				const int& numLines,
				const int& numCols,
				const int& startY,
				const int& startX)
{
  m_windowName.append(windowName);
  m_numLines = numLines;
  m_numCols = numCols;
  m_startY = startY;
  m_startX = startX;
} // end of "CursesWindow::DefineWindow"



/*
  Function:

  Description:
*/
WINDOW* CursesWindow::getWindow()
{
  return m_window;
} // end of "CursesWindow::getWindow"



/*
  Function:

  Description:
*/
const std::string& CursesWindow::getWindowName() const
{
  return m_windowName;
} // end of "CursesWindow::getWindowName"



/*
  Function:

  Description:
*/
const int& CursesWindow::getNumLines() const
{
  return m_numLines;
} // end of "CursesWindow::getNumLines"



/*
  Function:

  Description:
*/
const int& CursesWindow::getNumCols() const
{
  return m_numCols;
} // end of "CursesWindow::getNumCols"


/*
  Function:

  Description:
*/
const int& CursesWindow::getStartY() const
{
  return m_startY;
} // end  of "CursesWindow::getStartY"



/*
  Function:

  Description:
*/
const int& CursesWindow::getStartX() const
{
  return m_startX;
} // end of "CursesWindow::getStartX"



/*
  Function:

  Description:
*/
void CursesWindow::setWindow(WINDOW* window)
{ m_window = window;
} // end of "CursesWindow::setWindow"



/*
  Function:

  Description:
*/
void CursesWindow::setWindowName(const std::string winName)
{
  m_windowName = winName;
}



/*
  Function:

  Description:
*/
void CursesWindow::setNumLines(const int& numLines)
{
  m_numLines = numLines;
} // end of "CursesWindow::setNumLines"



/*
  Function:

  Description:
*/
void CursesWindow::setNumCols(const int& numCols)
{
  m_numCols = numCols;
} // end of "CursesWindow::setNumCols"



/*
  Function:

  Description:
*/
void CursesWindow::setStartY(const int& startY)
{
  m_startY = startY;
} // end of "CursesWindow::setStartY"



/*
  Function:

  Description:
*/
void CursesWindow::setStartX(const int& startX)
{
  m_startX = startX;
} // end of "CursesWindow::setStartX"



void CursesWindow::deleteWindow()
{
  delwin(getWindow());
  setWindow(nullptr);
}
