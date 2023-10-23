/*
  File:
   cpuWaWindow.hpp
   
  Description:
   The class definition for the CpuWaWindow class.
 */
#ifndef CPUWAWINDOW_HPP
#define CPUWAWINDOW_HPP
#include "cursesWindow.hpp"

class CpuWaWindow : public CursesWindow {
public:

  CpuWaWindow(WINDOW* win = nullptr,
	      const std::string windowName = "",	      
	      const short& numLines = 0,
	      const short& numCols = 0,
	      const short& startY = 0,
	      const short& startX = 0);
private:
};


#endif
