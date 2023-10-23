/*
  File:
   cpuNiWindow.hpp
   
  Description:
   The class definition for the CpuNiWindow class.
 */
#ifndef CPUNIWINDOW_HPP
#define CPUNIWINDOW_HPP
#include "cursesWindow.hpp"

class CpuNiWindow : public CursesWindow {
public:

  CpuNiWindow(WINDOW* win = nullptr,
	      const std::string windowName = "",	      
	      const short& numLines = 0,
	      const short& numCols = 0,
	      const short& startY = 0,
	      const short& startX = 0);
private:
};


#endif
