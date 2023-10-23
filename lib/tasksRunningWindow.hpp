/*
  File:
   TasksRunningWindow.hpp
   
  Description:
   The class definition for the TasksRunningWindow class.
 */
#ifndef TASKSRUNNINGWINDOW_HPP
#define TASKSRUNNINGWINDOW_HPP
#include "cursesWindow.hpp"

class TasksRunningWindow : public CursesWindow {
public:

  TasksRunningWindow(WINDOW* win = nullptr,
		     const std::string windowName = "",	      
		     const short& numLines = 0,
		     const short& numCols = 0,
		     const short& startY = 0,
		     const short& startX = 0);
private:
};


#endif
