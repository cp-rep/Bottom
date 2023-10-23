/*
  File:
   helpWindow.hpp
   
  Description:
   The class definition for the HelpWindow class.
 */
#ifndef HELPWINDOW_HPP
#define HELPWINDOW_HPP
#include "cursesWindow.hpp"

class HelpWindow : public CursesWindow {
public:

  HelpWindow(WINDOW* win = nullptr,
	     const std::string windowName = "",	      
	     const short& numLines = 0,
	     const short& numCols = 0,
	     const short& startY = 0,
	     const short& startX = 0);
private:
};


#endif
