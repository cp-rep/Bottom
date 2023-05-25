/*
  File: PIDWindow.hpp
  Description:
 */
#ifndef PIDWINDOW_HPP
#define PIDWINDOW_HPP
#include "cursesWindow.hpp"


class PIDWindow : public CursesWindow {
public:

  PIDWindow(std::string windowName = "",	      
	    const short& numLines = 0,
	    const short& numCols = 0,
	    const short& startY = 0,
	    const short& startX = 0);
private:
  
};

#endif
