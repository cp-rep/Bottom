/*
  File:
   topUpWindow.hpp
   
  Description:
   The class definition for the TopUpWindow class.
 */
#ifndef TOPUPWINDOW_HPP
#define TOPUPWINDOW_HPP
#include "cursesWindow.hpp"

class TopUpWindow : public CursesWindow {
public:

  TopUpWindow(WINDOW* win = nullptr,
	     const std::string windowName = "",	      
	     const short& numLines = 0,
	     const short& numCols = 0,
	     const short& startY = 0,
	     const short& startX = 0);
private:
};


#endif
