/*
  File: NIWindow.hpp
  Description:
 */
#ifndef NIWINDOW_HPP
#define NIWINDOW_HPP
#include "cursesWindow.hpp"

class NIWindow : public CursesWindow {
public:
  NIWindow(std::string windowName = "",	      
	   const short& numLines = 0,
	   const short& numCols = 0,
	   const short& startY = 0,
	   const short& startX = 0);

private:
};



#endif
