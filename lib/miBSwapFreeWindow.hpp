/*
  File:
   miBSwapFreeWindow.hpp
   
  Description:
   The class definition for the MiBSwapFreeWindow class.
 */
#ifndef MIBSWAPFREEWINDOW_HPP
#define MIBSWAPFREEWINDOW_HPP
#include "cursesWindow.hpp"

class MiBSwapFreeWindow : public CursesWindow {
public:

  MiBSwapFreeWindow(WINDOW* win = nullptr,
		    const std::string windowName = "",	      
		    const short& numLines = 0,
		    const short& numCols = 0,
		    const short& startY = 0,
		    const short& startX = 0);
private:
};


#endif
