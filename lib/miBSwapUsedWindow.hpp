/*
  File:
   miBSwapUsedWindow.hpp
   
  Description:
   The class definition for the MiBSwapUsedWindow class.
 */
#ifndef MIBSWAPUSEDWINDOW_HPP
#define MIBSWAPUSEDWINDOW_HPP
#include "cursesWindow.hpp"

class MiBSwapUsedWindow : public CursesWindow {
public:

  MiBSwapUsedWindow(WINDOW* win = nullptr,
		    const std::string windowName = "",	      
		    const short& numLines = 0,
		    const short& numCols = 0,
		    const short& startY = 0,
		    const short& startX = 0);
private:
};


#endif
