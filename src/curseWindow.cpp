/*
  File: curseWindow.cpp
 
  Description: The implementation of the CurseWindow class.
*/
#include "curseWindow.hpp"



/*
  Function:
  CurseWindow() Default Constructor
   
  Description:
  Initializes the main screen of the Top program.

  Input:
  curseWindow     -
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
CurseWindow::CurseWindow(WINDOW* window,
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
  defineWindow(window,
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
} // end of "CurseWindow Default Constructor"



/*
  Function:
  CurseWindow() Default Constructor
   
  Description:
  Initializes the main screen of the Top program.

  Input:
  curseWindow     -
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
void CurseWindow::defineWindow(WINDOW* window,
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
  m_window = window;
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
} // end of "CurseWindow::DefineWindow"



/*
  Function:

  Description:
*/
WINDOW* CurseWindow::getWindow()
{
  return m_window;
} // end of "CurseWindow::getWindow"



/*
  Function:

  Description:
*/
const int& CurseWindow::getNumLines() const
{
  return m_numLines;
} // end of "CurseWindow::getNumLines"



/*
  Function:

  Description:
*/
const int& CurseWindow::getNumCols() const
{
  return m_numCols;
} // end of "CurseWindow::getNumCols"



/*
  Function:

  Description:
*/
const int& CurseWindow::getMaxWindowY() const
{
  return m_maxWindowY;
} // end of "CurseWindow::getMaxWindowY"



/*
  Function:

  Description:
*/
const int& CurseWindow::getMaxWindowX() const
{
  return m_maxWindowX;
} // end of "CurseWindow::getMaxWindowX"



/*
  Function:

  Description:
*/
const int& CurseWindow::getMinWindowY() const
{
  return m_minWindowY;
} // end of "CurseWindow::getMinWindowY"



/*
  Function:

  Description:
*/
const int& CurseWindow::getMinWindowX() const
{
  return m_minWindowX;
} // end of "CurseWindow::getMinWindowX"



/*
  Function:

  Description:
*/
const int& CurseWindow::getCenterY() const
{
  return m_centerY;
} // end of "CurseWindow::getCenterY"



/*
  Function:

  Description:
*/
const int& CurseWindow::getCenterX() const
{
  return m_centerX;
} //  end  of "CurseWindow::getCenterX"



/*
  Function:

  Description:
*/
const int& CurseWindow::getStartY() const
{
  return m_startY;
} // end  of "CurseWindow::getStartY"



/*
  Function:

  Description:
*/
const int& CurseWindow::getStartX() const
{
  return m_startX;
} // end of "CurseWindow::getStartX"



/*
  Function:

  Description:
*/
const int& CurseWindow::getCurrentY() const
{
  return m_currentY;
} // end of "CurseWindow::getCurrentY"



/*
  Function:

  Description:
*/
const int& CurseWindow::getCurrentX() const
{
  return m_currentX;
} // end of "CurseWindow::getCurrentX"



/*
  Function:

  Description:
*/
const int& CurseWindow::getPreviousY() const
{
  return m_previousY;
} // end of  "CurseWindow::getPreviousY"



/*
  Function:

  Description:
*/
const int& CurseWindow::getPreviousX() const
{
  return m_previousX;
} // end of "CurseWindow::getPreviousX"



/*
  Function:

  Description:
*/
void CurseWindow::setWindow(WINDOW* window)
{ m_window = window;
} // end of "CurseWindow::setWindow"



/*
  Function:

  Description:
*/
void CurseWindow::setNumLines(const int& numLines)
{
  m_numLines = numLines;
} // end of "CurseWindow::setNumLines"



/*
  Function:

  Description:
*/
void CurseWindow::setNumCols(const int& numCols)
{
  m_numCols = numCols;
} // end of "CurseWindow::setNumCols"



/*
  Function:

  Description:
*/
void CurseWindow::setMaxWindowY(const int& maxWindowY)
{
  m_maxWindowY = maxWindowY;
} // end of "CurseWindow::setMaxWindowY"



/*
  Function:

  Description:
*/
void CurseWindow::setMaxWindowX(const int& maxWindowX)
{
  m_maxWindowX = maxWindowX;
} // end of "CurseWindow::setMaxWindowX"



/*
  Function:

  Description:
*/
void CurseWindow::setMinWindowY(const int& minWindowY)
{
  m_minWindowY = minWindowY;
} // end of "CurseWindow::setMinWindowY"



/*
  Function:

  Description:
*/
void CurseWindow::setMinWindowX(const int& minWindowX)
{
  m_minWindowX = minWindowX;
} // end of "CurseWindow::setMinWindowX"



/*
  Function:

  Description:
*/
void CurseWindow::setCenterY(const int& centerY)
{
  m_centerY = centerY;
} // end of "CurseWindow::setCenterY"



/*
  Function:

  Description:
*/
void CurseWindow::setCenterX(const int& centerX)
{
  m_centerX = centerX;
} // end of "CurseWindow::setCenterX"



/*
  Function:

  Description:
*/
void CurseWindow::setStartY(const int& startY)
{
  m_startY = startY;
} // end of "CurseWindow::setStartY"



/*
  Function:

  Description:
*/
void CurseWindow::setStartX(const int& startX)
{
  m_startX = startX;
} // end of "CurseWindow::setStartX"



/*
  Function:

  Description:
*/
void CurseWindow::setCurrentY(const int& currentY)
{
  m_currentY = currentY;
} // end of "CurseWindow::setCurrentY"



/*
  Function:

  Description:
*/
void CurseWindow::setCurrentX(const int& currentX)
{
  m_currentX = currentX;
} // end of "CurseWindow::setCurrentX"



/*
  Function:

  Description:
*/
void CurseWindow::setPreviousY(const int& previousY)
{
  m_previousY = previousY;
} // end of "CurseWindow::setPreviousY"



/*
  Function:

  Description:
*/
void CurseWindow::setPreviousX(const int& previousX)
{
  m_previousX = previousX;
} // end of "CurseWindow::setPreviousX"
