/*
  File: PRWindow.hpp
  Description:
 */
#ifndef PRWINDOW_HPP
#define PRWINDOW_HPP
#include "cursesWindow.hpp"

class PRWindow : public CursesWindow {
public:
  PRWindow(std::string windowName = "",
	   const short& numLines = 0,
	   const short& numCols = 0,
	   const short& startY = 0,
	   const short& startX = 0);
private:
};

#endif
