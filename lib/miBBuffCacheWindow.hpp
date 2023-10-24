/*
  File:
   miBBuffCacheWindow.hpp
   
  Description:
   The class definition for the MiBBuffCacheWindow class.
 */
#ifndef MIBBUFFCACHEWINDOW_HPP
#define MIBBUFFCACHEWINDOW_HPP
#include "cursesWindow.hpp"

class MiBBuffCacheWindow : public CursesWindow {
public:

  MiBBuffCacheWindow(WINDOW* win = nullptr,
	     const std::string windowName = "",	      
	     const short& numLines = 0,
	     const short& numCols = 0,
	     const short& startY = 0,
	     const short& startX = 0);
private:
};


#endif
