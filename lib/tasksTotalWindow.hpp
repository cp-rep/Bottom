/*
  File:
   TasksTotalWindow.hpp
   
  Description:
   The class definition for the TasksTotalWindow class.
 */
#ifndef TASKSTOTALWINDOW_HPP
#define TASKSTOTALWINDOW_HPP
#include "cursesWindow.hpp"

class TasksTotalWindow : public CursesWindow {
public:

  TasksTotalWindow(WINDOW* win = nullptr,
		   const std::string windowName = "",	      
		   const short& numLines = 0,
		   const short& numCols = 0,
		   const short& startY = 0,
		   const short& startX = 0);
private:
};


#endif
