/*
  File:
   TasksZombieWindow.hpp
   
  Description:
   The class definition for the TasksZombieWindow class.
 */
#ifndef TasksZombieWINDOW_HPP
#define TasksZombieWINDOW_HPP
#include "cursesWindow.hpp"

class TasksZombieWindow : public CursesWindow {
public:

  TasksZombieWindow(WINDOW* win = nullptr,
		    const std::string windowName = "",	      
		    const short& numLines = 0,
		    const short& numCols = 0,
		    const short& startY = 0,
		    const short& startX = 0);
private:
};


#endif
