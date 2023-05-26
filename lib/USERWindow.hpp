/*
  File: USERWindow.hpp
  Description:
 */
#ifndef USERWINDOW_HPP
#define USERWINDOW_HPP
#include "cursesWindow.hpp"

class USERWindow : public CursesWindow {
public:

  USERWindow(WINDOW* win = nullptr,
	     const std::string windowName = "",	      
	     const short& numLines = 0,
	     const short& numCols = 0,
	     const short& startY = 0,
	     const short& startX = 0);
private:
};


#endif
