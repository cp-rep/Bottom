/*
  File:
   cpuUsWindow.hpp
   
  Description:
   The class definition for the CpuUsWindow class.
 */
#ifndef CPUUSWINDOW_HPP
#define CPUUSWINDOW_HPP
#include "cursesWindow.hpp"

class CpuUsWindow : public CursesWindow {
public:

  CpuUsWindow(WINDOW* win = nullptr,
	     const std::string windowName = "",	      
	     const short& numLines = 0,
	     const short& numCols = 0,
	     const short& startY = 0,
	     const short& startX = 0);
private:
};


#endif
