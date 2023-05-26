/*
  File: SHRWindow.hpp
  Description:
 */
#ifndef SHRWINDOW_HPP
#define SHRWINDOW_HPP
#include "cursesWindow.hpp"

class SHRWindow : public CursesWindow {
public:
  SHRWindow(WINDOW* win = nullptr,
	    const std::string windowName = "",	      
	    const short& numLines = 0,
	    const short& numCols = 0,
	    const short& startY = 0,
	    const short& startX = 0);
private:
};



#endif
