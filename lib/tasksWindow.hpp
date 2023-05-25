/*
  File: tasksWindow.hpp
  Description:
 */
#ifndef TASKSWINDOW_HPP
#define TASKSWINDOW_HPP
#include "cursesWindow.hpp"

class TasksWindow : public CursesWindow {
public:
  TasksWindow(std::string windowName = "",	      
	      const short& numLines = 0,
	      const short& numCols = 0,
	      const short& startY = 0,
	      const short& startX = 0);
private:
};

#endif
