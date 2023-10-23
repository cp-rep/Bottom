/*
  File: 
   tasksWindow.hpp

  Description:
   The class definition for the TasksWindow class.
   
   For output "Tasks: XXX total, XXX running, XXX sleeping...".
*/
#ifndef TASKSWINDOW_HPP
#define TASKSWINDOW_HPP
#include "cursesWindow.hpp"

class TasksWindow : public CursesWindow {
public:
  TasksWindow(WINDOW* win = nullptr,
	      const std::string& windowName = "",
	      const short& numLines = 0,
	      const short& numCols = 0,
	      const short& startY = 0,
	      const short& startX = 0);

  // member functions
  void defineTasksLine(const unsigned int& total,
		       const unsigned int& running,
		       const unsigned int& sleeping,
		       const unsigned int& stopped,
		       const unsigned int& zombie);
  // getters
  const std::string& getTasksLine();

  // setters
  void setTasksLine(const std::string& tasksLine);
  
private:
  std::string m_tasksLine;
};

#endif
