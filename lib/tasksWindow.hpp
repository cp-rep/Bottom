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
	      const std::string windowName = "",
	      const short& numLines = 0,
	      const short& numCols = 0,
	      const short& startY = 0,
	      const short& startX = 0);

  // member functions
  void defineTasksWindow(const unsigned int& total,
			 const unsigned int& running,
			 const unsigned int& sleeping,
			 const unsigned int& stopped,
			 const unsigned int& zombie)
  {
    m_tasksLine = "Tasks: ";
    m_tasksLine.append(std::to_string(total));
    m_tasksLine.append(" total, ");
    m_tasksLine.append(std::to_string(running));
    m_tasksLine.append(" running, ");
    m_tasksLine.append(std::to_string(sleeping));
    m_tasksLine.append(" sleeping, ");
    m_tasksLine.append(std::to_string(stopped));
    m_tasksLine.append(" stopped, ");
    m_tasksLine.append(std::to_string(zombie));
    m_tasksLine.append(" zombie");    
  }

  // getters
  const std::string& getTasksLine() { return m_tasksLine; }

  // setters
  void setTasksLine(const std::string& tasksLine) { m_tasksLine = tasksLine; }
  
private:
  std::string m_tasksLine;
};

#endif
