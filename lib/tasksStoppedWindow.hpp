/*
  File:
   TasksStoppedWindow.hpp
   
  Description:
   The class definition for the TasksStoppedWindow class.
 */
#ifndef TASKSSTOPPEDWINDOW_HPP
#define TASKSSTOPPEDWINDOW_HPP
#include "cursesWindow.hpp"

class TasksStoppedWindow : public CursesWindow {
public:

  TasksStoppedWindow(WINDOW* win = nullptr,
		     const std::string windowName = "",	      
		     const short& numLines = 0,
		     const short& numCols = 0,
		     const short& startY = 0,
		     const short& startX = 0);
private:
};


#endif
