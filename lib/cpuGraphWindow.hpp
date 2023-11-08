/*
  File: 
   cpuGraphWindow.hpp

  Description:
   The class definition for the CpuGraphWindow class.
*/
#ifndef CPUGRAPHWINDOW_HPP
#define CPUGRAPHWINDOW_HPP
#include "cursesWindow.hpp"

class CpuGraphWindow : public CursesWindow {
public:
  CpuGraphWindow(WINDOW* win = nullptr,
	      const std::string& windowName = "",
	      const short& numLines = 0,
	      const short& numCols = 0,
	      const short& startY = 0,
	      const short& startX = 0);
private:
};

#endif
