/*
  File:
   miBMemTotalWindow.hpp
   
  Description:
   The class definition for the MiBMemTotalWindow class.
 */
#ifndef MIBMEMTOTALWINDOW_HPP
#define MIBMEMTOTALWINDOW_HPP
#include "cursesWindow.hpp"

class MiBMemTotalWindow : public CursesWindow {
public:

  MiBMemTotalWindow(WINDOW* win = nullptr,
		    const std::string windowName = "",	      
		    const short& numLines = 0,
		    const short& numCols = 0,
		    const short& startY = 0,
		    const short& startX = 0);
private:
};


#endif
