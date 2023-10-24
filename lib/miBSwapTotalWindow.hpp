/*
  File:
   miBSwapTotalWindow.hpp
   
  Description:
   The class definition for the MiBSwapTotalWindow class.
 */
#ifndef MIBSWAPTOTALWINDOW_HPP
#define MIBSWAPTOTALWINDOW_HPP
#include "cursesWindow.hpp"

class MiBSwapTotalWindow : public CursesWindow {
public:

  MiBSwapTotalWindow(WINDOW* win = nullptr,
	     const std::string windowName = "",	      
	     const short& numLines = 0,
	     const short& numCols = 0,
	     const short& startY = 0,
	     const short& startX = 0);
private:
};


#endif
