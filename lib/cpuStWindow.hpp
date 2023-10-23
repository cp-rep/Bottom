/*
  File:
   cpuStWindow.hpp
   
  Description:
   The class definition for the CpuStWindow class.
 */
#ifndef CPUSTWINDOW_HPP
#define CPUSTWINDOW_HPP
#include "cursesWindow.hpp"

class CpuStWindow : public CursesWindow {
public:

  CpuStWindow(WINDOW* win = nullptr,
	      const std::string windowName = "",	      
	      const short& numLines = 0,
	      const short& numCols = 0,
	      const short& startY = 0,
	      const short& startX = 0);
private:
};


#endif
