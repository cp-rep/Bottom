// ============================================================================
// File: curseWindow.cpp
// Description: The implementation of the CurseWindow class.
// ============================================================================
#include "curseWindow.hpp"



// ==== CurseWindow Default Constructor =======================================
// Description:
//  Initializes the main window of the Top program.
//
// Input:
//  curseWindow      -
//  numLines        -
//  numCols         -
//  maxWindowY      -
//  maxWindowX      -
//  minWindowY      -
//  minWindowX      -
//  centerY         -
//  centerX         -
//  startY          -
//  startX          -
//  currentY        -
//  currentX        -
//  previousY       -
//  previousX       -
//
// Output:
//  None
// ============================================================================
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
} // end of "CurseWindow Default Constructor"



// ==== CurseWindow::setWindow ================================================
// 
// ============================================================================
void CurseWindow::setWindow(WINDOW* window)
{ m_window = window;
} // end of "CurseWindow::setWindow"


// ==== CurseWindow::setWindow ================================================
// 
// ============================================================================
WINDOW* CurseWindow::getWindow()
{
  return m_window;
} // end of "CurseWindow::setWindow"



// ==== CurseWindow::setNumLines ==============================================
// 
// ============================================================================
void CurseWindow::setNumLines(const int& numLines)
{
} // end of "CurseWindow::setNumLines"



// ==== CurseWindow::setNumCols ===============================================
// 
// ============================================================================
void CurseWindow::setNumCols(const int& numCols)
{
} // end of "CurseWindow::setNumCols"



// ==== CurseWindow::setMaxWindowY ============================================
// 
// ============================================================================
void CurseWindow::setMaxWindowY(const int& maxWindowY)
{
} // end of "CurseWindow::setMaxWindowY"



// ==== CurseWindow::setMaxWindowX ============================================
// 
// ============================================================================
void CurseWindow::setMaxWindowX(const int& maxWindowX)
{
} // end of "CurseWindow::setMaxWindowX"



// ==== CurseWindow::setMinWindowY ============================================
// 
// ============================================================================
void CurseWindow::setMinWindowY(const int& minWindowY)
{
} // end of "CurseWindow::setMinWindowY"



// ==== CurseWindow::setMinWindowX ============================================
// 
// ============================================================================
void CurseWindow::setMinWindowX(const int& minWindowX)
{ 
} // end of "CurseWindow::setMinWindowX"



// ==== CurseWindow::setCenterY ===============================================
// 
// ============================================================================
void CurseWindow::setCenterY(const int& centerY)
{
} // end of "CurseWindow::setCenterY"



// ==== CurseWindow::setCenterX ===============================================
// 
// ============================================================================
void CurseWindow::setCenterX(const int& centerX)
{
} // end of "CurseWindow::setCenterX"



// ==== CurseWindow::setStartY ================================================
// 
// ============================================================================
void CurseWindow::setStartY(const int& startY)
{
} // end of "CurseWindow::setStartY"



// ==== CurseWindow::setStartX ================================================
// 
// ============================================================================
void CurseWindow::setStartX(const int& startX)
{
} // end of "CurseWindow::setStartX"



// ==== CurseWindow::setCurrentY ==============================================
// 
// ============================================================================
void CurseWindow::setCurrentY(const int& currentY)
{
} // end of "CurseWindow::setCurrentY"



// ==== CurseWindow::setCurrentX ==============================================
// 
// ============================================================================
void CurseWindow::setCurrentX(const int& currentX)
{
} // end of "CurseWindow::setCurrentX"



// ==== CurseWindow::setPreviousY =============================================
// 
// ============================================================================
void CurseWindow::setPreviousY(const int& previousY)
{
} // end of "CurseWindow::setPreviousY"



// ==== CurseWindow::setPreviousX =============================================
// 
// ============================================================================
void CurseWindow::setPreviousX(const int& previousX)
{
} // end of "CurseWindow::setPreviousX"
