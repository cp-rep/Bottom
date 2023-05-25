/*
  File: VIRTWindow.hpp
  Description:
 */
#ifndef VIRTWINDOW_HPP
#define VIRTWINDOW_HPP
#include "cursesWindow.hpp"

class VIRTWindow : public CursesWindow {
public:
  VIRTWindow(std::string windowName = "",	      
	     const short& numLines = 0,
	     const short& numCols = 0,
	     const short& startY = 0,
	     const short& startX = 0);

private:
};



#endif
