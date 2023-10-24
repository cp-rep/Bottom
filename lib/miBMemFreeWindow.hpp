/*
  File:
   miBMemFreeWindow.hpp
   
  Description:
   The class definition for the MiBMemFreeWindow class.
 */
#ifndef MIBMEMFREEWINDOW_HPP
#define MIBMEMFREEWINDOW_HPP
#include "cursesWindow.hpp"

class MiBMemFreeWindow : public CursesWindow {
public:

  MiBMemFreeWindow(WINDOW* win = nullptr,
		   const std::string windowName = "",	      
		   const short& numLines = 0,
		   const short& numCols = 0,
		   const short& startY = 0,
		   const short& startX = 0);
private:
};


#endif
