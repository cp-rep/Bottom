/*
  File:
   VIRTWindow.hpp
   
  Description:
   The class definition for the VIRTWindow class.
*/
#ifndef VIRTWINDOW_HPP
#define VIRTWINDOW_HPP
#include "cursesWindow.hpp"

class VIRTWindow : public CursesWindow {
public:
  VIRTWindow(WINDOW* win = nullptr,
	     const std::string windowName = "",	      
	     const short& numLines = 0,
	     const short& numCols = 0,
	     const short& startY = 0,
	     const short& startX = 0);

private:
};

#endif
