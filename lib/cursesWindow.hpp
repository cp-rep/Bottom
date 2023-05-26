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
  CursesWindow(WINDOW* win = nullptr,
	       const std::string windowName = "",	      
	       const int& numLines = 0,
	       const int& numCols = 0,
	       const int& startY = 0,
	       const int& startX = 0);

  // destructor
  ~CursesWindow();

  // member functions
  void defineWindow(WINDOW* win,
		    const std::string windowName,
		    const int& numLines,
		    const int& numCols,
		    const int& startY,
		    const int& startX);
  void deleteWindow();
  
  // getters
  WINDOW* getWindow();
  const std::string& getWindowName() const;
  const int& getNumCols() const;
  const int& getNumLines() const;
  const int& getStartY() const;
  const int& getStartX() const;
  
  // setters
  void setWindow(WINDOW* window);
  void setWindowName(const std::string winName);
  void setNumLines(const int& numLines);
  void setNumCols(const int& numCols);
  void setStartY(const int& startY);
  void setStartX(const int& startX);
  
private:
  // member variables
  WINDOW* m_window;
  std::string m_windowName;
  int m_numLines;
  int m_numCols;
  int m_startY;
  int m_startX;
};

#endif
