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
		   const short& maxWindowY  = 0,
		   const short& maxWindowX = 0,
		   const short& minWindowY = 0,
		   const short& minWindowX = 0,
		   const short& centerY = 0,
		   const short& centerX = 0,
		   const short& startY = 0,
		   const short& startX = 0,
		   const short& currentY = 0,
		   const short& currentX = 0,
		   const short& previousY =  0,
		   const short& previousX = 0);  
private:
};

#endif
