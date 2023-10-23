/*
  File:
   TasksSleepingWindow.hpp
   
  Description:
   The class definition for the TasksSleepingWindow class.
 */
#ifndef TASKSSLEEPINGWINDOW_HPP
#define TASKSSLEEPINGWINDOW_HPP
#include "cursesWindow.hpp"

class TasksSleepingWindow : public CursesWindow {
public:

  TasksSleepingWindow(WINDOW* win = nullptr,
		      const std::string windowName = "",	      
		      const short& numLines = 0,
		      const short& numCols = 0,
		      const short& startY = 0,
		      const short& startX = 0);
private:
};


#endif
