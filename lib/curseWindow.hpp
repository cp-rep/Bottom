// ============================================================================
// File: curseWindow.hpp
// Description:
// ============================================================================
#ifndef CURSEWINDOW_HPP
#define CURSEWINDOW_HPP
#include <curses.h>



// will represent the main screen window
class CurseWindow {
public:
  // constructors and destructor
  CurseWindow(WINDOW* curseWindow = nullptr,
	      const int& numLines = 0,
	      const int& numCols = 0,
	      const int& maxWindowY  = 0,
	      const int& maxWindowX = 0,
	      const int& minWindowY = 0,
	      const int& minWindowX = 0,
	      const int& centerY = 0,
	      const int& centerX = 0,
	      const int& startY = 0,
	      const int& startX = 0,
	      const int& currentY = 0,
	      const int& currentX = 0,
	      const int& previousY =  0,
	      const int& previousX = 0);

  // member functions
  void setNumLines(const int& numLines);
  void setNumCols(const int& numCols);
  void setMaxWindowY(const int& maxWindowY);
  void setMaxWindowX(const int& maxWindowX);
  void setMinWindowY(const int& minWindowY);
  void setMinWindowX(const int& minWindowX);
  void setCenterY(const int& centerY);
  void setCenterX(const int& centerX);
  void setStartY(const int& startY);
  void setStartX(const int& startX);
  void setCurrentY(const int& currentY);
  void setCurrentX(const int& currentX);
  void setPreviousY(const int& previousY);
  void setPreviousX(const int& previousX);
  
private:
  // member variables
  WINDOW* m_curseWindow;  
  int m_numLines;
  int m_numCols;
  int m_maxWindowY;
  int m_maxWindowX;
  int m_minWindowY;
  int m_minWindowX;
  int m_centerY;
  int m_centerX;
  int m_startY;
  int m_startX;
  int m_currentY;
  int m_currentX;
  int m_previousY;
  int m_previousX;
};

#endif
