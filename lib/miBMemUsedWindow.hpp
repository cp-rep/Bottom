/*
  File:
   miBMemUsedWindow.hpp
   
  Description:
   The class definition for the MiBMemUsedWindow class.
 */
#ifndef MIBMEMUSEDWINDOW_HPP
#define MIBMEMUSEDWINDOW_HPP
#include "cursesWindow.hpp"

class MiBMemUsedWindow : public CursesWindow {
public:

  MiBMemUsedWindow(WINDOW* win = nullptr,
	     const std::string windowName = "",	      
	     const short& numLines = 0,
	     const short& numCols = 0,
	     const short& startY = 0,
	     const short& startX = 0);
private:
};


#endif
