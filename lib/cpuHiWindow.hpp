/*
  File:
   cpuHiWindow.hpp
   
  Description:
   The class definition for the CpuHiWindow class.
 */
#ifndef CPUHIWINDOW_HPP
#define CPUHIWINDOW_HPP
#include "cursesWindow.hpp"

class CpuHiWindow : public CursesWindow {
public:

  CpuHiWindow(WINDOW* win = nullptr,
	      const std::string windowName = "",	      
	      const short& numLines = 0,
	      const short& numCols = 0,
	      const short& startY = 0,
	      const short& startX = 0);
private:
};


#endif
