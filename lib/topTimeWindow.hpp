/*
  File:
   topTimeWindow.hpp
   
  Description:
   The class definition for the TopTimeWindow class.
 */
#ifndef TOPTIMEWINDOW_HPP
#define TOPTIMEWINDOW_HPP
#include "cursesWindow.hpp"

class TopTimeWindow : public CursesWindow {
public:

  TopTimeWindow(WINDOW* win = nullptr,
		const std::string windowName = "",	      
		const short& numLines = 0,
		const short& numCols = 0,
		const short& startY = 0,
		const short& startX = 0);
private:
};


#endif
