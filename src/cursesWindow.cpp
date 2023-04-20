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
  None
*/
CursesWindow::CursesWindow(std::string windowName,
			   const int& numLines,
			   const int& numCols,
			   const int& maxWindowY,
			   const int& maxWindowX,
			   const int& minWindowY,
			   const int& minWindowX,
			   const int& centerY,
			   const int& centerX,
			   const int& startY,
			   const int& startX,
			   const int& currentY,
			   const int& currentX,
			   const int& previousY,
			   const int& previousX)
{
  defineWindow(windowName,
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
	       previousX);
} // end of "CursesWindow Default Constructor"



/*
  Function:
   defineWindow
   
  Description:
   Defines the values/dimensions for the named window.

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
  None
*/
void CursesWindow::defineWindow(std::string windowName,
				const int& numLines,
				const int& numCols,
				const int& maxWindowY,
				const int& maxWindowX,
				const int& minWindowY,
				const int& minWindowX,
				const int& centerY,
				const int& centerX,
				const int& startY,
				const int& startX,
				const int& currentY,
				const int& currentX,
				const int& previousY,
				const int& previousX)
{
  m_windowName.append(windowName);
  m_numLines = numLines;
  m_numCols = numCols;
  m_maxWindowY = maxWindowY;
  m_maxWindowX = maxWindowX;
  m_minWindowY = minWindowY;
  m_minWindowX = minWindowX;
  m_centerY = centerY;
  m_centerX = centerX;
  m_startY = startY;
  m_startX = startX;
  m_currentY = currentY;
  m_currentX = currentX;
  m_previousY = previousY;
  m_previousX = previousX;
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
const int& CursesWindow::getMaxWindowY() const
{
  return m_maxWindowY;
} // end of "CursesWindow::getMaxWindowY"



/*
  Function:

  Description:
*/
const int& CursesWindow::getMaxWindowX() const
{
  return m_maxWindowX;
} // end of "CursesWindow::getMaxWindowX"



/*
  Function:

  Description:
*/
const int& CursesWindow::getMinWindowY() const
{
  return m_minWindowY;
} // end of "CursesWindow::getMinWindowY"



/*
  Function:

  Description:
*/
const int& CursesWindow::getMinWindowX() const
{
  return m_minWindowX;
} // end of "CursesWindow::getMinWindowX"



/*
  Function:

  Description:
*/
const int& CursesWindow::getCenterY() const
{
  return m_centerY;
} // end of "CursesWindow::getCenterY"



/*
  Function:

  Description:
*/
const int& CursesWindow::getCenterX() const
{
  return m_centerX;
} //  end  of "CursesWindow::getCenterX"



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
const int& CursesWindow::getCurrentY() const
{
  return m_currentY;
} // end of "CursesWindow::getCurrentY"



/*
  Function:

  Description:
*/
const int& CursesWindow::getCurrentX() const
{
  return m_currentX;
} // end of "CursesWindow::getCurrentX"



/*
  Function:

  Description:
*/
const int& CursesWindow::getPreviousY() const
{
  return m_previousY;
} // end of  "CursesWindow::getPreviousY"



/*
  Function:

  Description:
*/
const int& CursesWindow::getPreviousX() const
{
  return m_previousX;
} // end of "CursesWindow::getPreviousX"



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
void CursesWindow::setMaxWindowY(const int& maxWindowY)
{
  m_maxWindowY = maxWindowY;
} // end of "CursesWindow::setMaxWindowY"



/*
  Function:

  Description:
*/
void CursesWindow::setMaxWindowX(const int& maxWindowX)
{
  m_maxWindowX = maxWindowX;
} // end of "CursesWindow::setMaxWindowX"



/*
  Function:

  Description:
*/
void CursesWindow::setMinWindowY(const int& minWindowY)
{
  m_minWindowY = minWindowY;
} // end of "CursesWindow::setMinWindowY"



/*
  Function:

  Description:
*/
void CursesWindow::setMinWindowX(const int& minWindowX)
{
  m_minWindowX = minWindowX;
} // end of "CursesWindow::setMinWindowX"



/*
  Function:

  Description:
*/
void CursesWindow::setCenterY(const int& centerY)
{
  m_centerY = centerY;
} // end of "CursesWindow::setCenterY"



/*
  Function:

  Description:
*/
void CursesWindow::setCenterX(const int& centerX)
{
  m_centerX = centerX;
} // end of "CursesWindow::setCenterX"



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



/*
  Function:

  Description:
*/
void CursesWindow::setCurrentY(const int& currentY)
{
  m_currentY = currentY;
} // end of "CursesWindow::setCurrentY"



/*
  Function:

  Description:
*/
void CursesWindow::setCurrentX(const int& currentX)
{
  m_currentX = currentX;
} // end of "CursesWindow::setCurrentX"



/*
  Function:

  Description:
*/
void CursesWindow::setPreviousY(const int& previousY)
{
  m_previousY = previousY;
} // end of "CursesWindow::setPreviousY"



/*
  Function:

  Description:
*/
void CursesWindow::setPreviousX(const int& previousX)
{
  m_previousX = previousX;
} // end of "CursesWindow::setPreviousX"
