/*
  File: SWindow.hpp
  Description:
 */
#ifndef SWINDOW_HPP
#define SWINDOW_HPP
#include "cursesWindow.hpp"

class SWindow : public CursesWindow {
public:
  SWindow(WINDOW* win = nullptr,
	  const std::string windowName = "",	      
	  const short& numLines = 0,
	  const short& numCols = 0,
	  const short& startY = 0,
	  const short& startX = 0);
private:
};



#endif
