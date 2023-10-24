/*
  File:
   cpuSiWindow.hpp
   
  Description:
   The class definition for the CpuSiWindow class.
 */
#ifndef CPUSIWINDOW_HPP
#define CPUSIWINDOW_HPP
#include "cursesWindow.hpp"

class CpuSiWindow : public CursesWindow {
public:

  CpuSiWindow(WINDOW* win = nullptr,
	     const std::string windowName = "",	      
	     const short& numLines = 0,
	     const short& numCols = 0,
	     const short& startY = 0,
	     const short& startX = 0);
private:
};


#endif