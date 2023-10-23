/*
  File:
   cpuSyWindow.hpp
   
  Description:
   The class definition for the CpuSyWindow class.
 */
#ifndef CPUSYWINDOW_HPP
#define CPUSYWINDOW_HPP
#include "cursesWindow.hpp"

class CpuSyWindow : public CursesWindow {
public:

  CpuSyWindow(WINDOW* win = nullptr,
	      const std::string windowName = "",	      
	      const short& numLines = 0,
	      const short& numCols = 0,
	      const short& startY = 0,
	      const short& startX = 0);
private:
};


#endif
