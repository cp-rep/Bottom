/*
  File: RESWindow.hpp
  Description:
 */
#ifndef RESWINDOW_HPP
#define RESWINDOW_HPP
#include "cursesWindow.hpp"

class RESWindow : public CursesWindow {
public:
  RESWindow(std::string windowName = "",	      
	    const short& numLines = 0,
	    const short& numCols = 0,
	    const short& startY = 0,
	    const short& startX = 0);
private:
};


#endif
