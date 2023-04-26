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
  // constructors
  CursesWindow(std::string windowName = "",	      
	       const short& numLines = 0,
	       const short& numCols = 0,
	       const short& maxWindowY  = 0,
	       const short& maxWindowX = 0,
	       const short& minWindowY = 0,
	       const short& minWindowX = 0,
	       const short& centerY = 0,
	       const short& centerX = 0,
	       const short& startY = 0,
	       const short& startX = 0,
	       const short& currentY = 0,
	       const short& currentX = 0,
	       const short& previousY =  0,
	       const short& previousX = 0);

  // member functions
  void defineWindow(std::string windowName,
		    const short& numLines,
		    const short& numCols,
		    const short& maxWindowY,
		    const short& maxWindowX,
		    const short& minWindowY,
		    const short& minWindowX,
		    const short& centerY,
		    const short& centerX,
		    const short& startY,
		    const short& startX,
		    const short& currentY,
		    const short& currentX,
 		    const short& previousY,
		    const short& previousX);
  
  // getters
  WINDOW* getWindow();
  const std::string& getWindowName() const;
  const short& getNumCols() const;
  const short& getNumLines() const;
  const short& getMaxWindowY() const;
  const short& getMaxWindowX() const;
  const short& getMinWindowY() const;
  const short& getMinWindowX() const;  
  const short& getCenterY() const;
  const short& getCenterX() const;
  const short& getStartY() const;
  const short& getStartX() const;
  const short& getCurrentY() const;
  const short& getCurrentX() const;
  const short& getPreviousY() const;
  const short& getPreviousX() const;  

  // setters
  void setWindow(WINDOW* window);
  void setNumLines(const short& numLines);
  void setNumCols(const short& numCols);
  void setMaxWindowY(const short& maxWindowY);
  void setMaxWindowX(const short& maxWindowX);
  void setMinWindowY(const short& minWindowY);
  void setMinWindowX(const short& minWindowX);
  void setCenterY(const short& centerY);
  void setCenterX(const short& centerX);
  void setStartY(const short& startY);
  void setStartX(const short& startX);
  void setCurrentY(const short& currentY);
  void setCurrentX(const short& currentX);
  void setPreviousY(const short& previousY);
  void setPreviousX(const short& previousX);
  
private:
  // member variables
  WINDOW* m_window;
  std::string m_windowName;
  short m_numLines;
  short m_numCols;
  short m_maxWindowY;
  short m_maxWindowX;
  short m_minWindowY;
  short m_minWindowX;
  short m_centerY;
  short m_centerX;
  short m_startY;
  short m_startX;
  short m_currentY;
  short m_currentX;
  short m_previousY;
  short m_previousX;
};

#endif
