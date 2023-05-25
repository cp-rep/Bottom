/*
  File: TIMEWindow.hpp
  Description:
 */
#ifndef TIMEWINDOW_HPP
#define TIMEWINDOW_HPP

#include "cursesWindow.hpp"

class TIMEWindow : public CursesWindow {
public:
  TIMEWindow(std::string windowName = "",	      
	     const short& numLines = 0,
	     const short& numCols = 0,
	     const short& startY = 0,
	     const short& startX = 0);
private:
};

#endif
