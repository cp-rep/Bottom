/*
  File:
   TIMEWindow.hpp
   
  Description:
   The class definition for the USERWindow class.
 */
#ifndef TIMEWINDOW_HPP
#define TIMEWINDOW_HPP

#include "cursesWindow.hpp"

class TIMEWindow : public CursesWindow {
public:
  TIMEWindow(WINDOW* win = nullptr,
	     const std::string windowName = "",	      
	     const short& numLines = 0,
	     const short& numCols = 0,
	     const short& startY = 0,
	     const short& startX = 0);
private:
};

#endif
