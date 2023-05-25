/*
  File: percentMEMWindow.hpp
  Description:
 */
#ifndef PERCENTMEMWINDOW_HPP
#define PERCENTMEMWINDOW_HPP
#include "cursesWindow.hpp"

class PercentMEMWindow : public CursesWindow {
public:
  PercentMEMWindow(std::string windowName = "",	      
		   const short& numLines = 0,
		   const short& numCols = 0,
		   const short& startY = 0,
		   const short& startX = 0);
private:
};

#endif
