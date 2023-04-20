/*
  File: cursesWindow.hpp
  Description:
*/
#ifndef CURSESWINDOW_HPP
#define CURSESWINDOW_HPP
#include <curses.h>
#include <string>



class CursesWindow {
public:
  // constructors and destructor
  CursesWindow(std::string windowName = "",	      
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
  void defineWindow(std::string windowName,
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
		    const int& previousX);
  
  // getters
  WINDOW* getWindow();
  const std::string& getWindowName() const;
  const int& getNumCols() const;
  const int& getNumLines() const;
  const int& getMaxWindowY() const;
  const int& getMaxWindowX() const;
  const int& getMinWindowY() const;
  const int& getMinWindowX() const;  
  const int& getCenterY() const;
  const int& getCenterX() const;
  const int& getStartY() const;
  const int& getStartX() const;
  const int& getCurrentY() const;
  const int& getCurrentX() const;
  const int& getPreviousY() const;
  const int& getPreviousX() const;  

  // setters
  void setWindow(WINDOW* window);
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
  WINDOW* m_window;
  std::string m_windowName;
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
