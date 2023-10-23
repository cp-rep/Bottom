/*
  File:
   cpuIdWindow.hpp
   
  Description:
   The class definition for the CpuIdWindow class.
 */
#ifndef CPUIDWINDOW_HPP
#define CPUIDWINDOW_HPP
#include "cursesWindow.hpp"

class CpuIdWindow : public CursesWindow {
public:

  CpuIdWindow(WINDOW* win = nullptr,
	      const std::string windowName = "",	      
	      const short& numLines = 0,
	      const short& numCols = 0,
	      const short& startY = 0,
	      const short& startX = 0);
private:
};


#endif
