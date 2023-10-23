/*
  File:
   topLoadWindow.hpp
   
  Description:
   The class definition for the TopLoadWindow class.
 */
#ifndef TOPLOADWINDOW_HPP
#define TOPLOADWINDOW_HPP
#include "cursesWindow.hpp"

class TopLoadWindow : public CursesWindow {
public:

  TopLoadWindow(WINDOW* win = nullptr,
		const std::string windowName = "",	      
		const short& numLines = 0,
		const short& numCols = 0,
		const short& startY = 0,
		const short& startX = 0);
private:
};


#endif
