/*
  File:
   miBMemAvailWindow.hpp
   
  Description:
   The class definition for the MiBMemAvailWindow class.
 */
#ifndef MIBMEMAVAILWINDOW_HPP
#define MIBMEMAVAILWINDOW_HPP
#include "cursesWindow.hpp"

class MiBMemAvailWindow : public CursesWindow {
public:

  MiBMemAvailWindow(WINDOW* win = nullptr,
		    const std::string windowName = "",	      
		    const short& numLines = 0,
		    const short& numCols = 0,
		    const short& startY = 0,
		    const short& startX = 0);
private:
};


#endif
