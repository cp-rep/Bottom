/*
  File:
   tasksWindow.cpp
   
  Description:
   Class implementation for the TasksWindow class.
 */
#include "tasksWindow.hpp"



/*
  Function:
   TasksWindow Constructor
   
  Description:
   The class constructor for creating TasksWindow objects and 
   initializing related object data.

  Input:
   win                  - a pointer to a NCurses window that contains the 
                          address to the newly created Window.

   windowName           - a const reference to the name to be stored in
                          Window's private member variable m_window.

   numLines             - a const int reference to the max number of lines of the
                          created Window.

   numCols              - a const int reference to the max number of columns of
                          the created Window.
 
   startY               - a const int reference that defines the logical starting
                          line number of the Window.

   startX               - a const int reference that defines the logical starting
                          column number of the Window.

  Output:
  NONE
*/
TasksWindow::TasksWindow(WINDOW* win,
			 const std::string& windowName,	      
			 const short& numLines,
			 const short& numCols,
			 const short& startY,
			 const short& startX) : CursesWindow(win,
							     windowName,
							     numLines,
							     numCols,
							     startY,
							     startX)
{
} // end of "TasksWindow Constructor"



/*
  Function:
   defineTasksLine
   
  Description:


  Input:

  Output
   'NONE
*/
void TasksWindow::defineTasksLine(const unsigned int& total,
				  const unsigned int& running,
				  const unsigned int& sleeping,
				  const unsigned int& stopped,
				  const unsigned int& zombie)
{
  std::lock_guard<std::mutex> lock(m_tasksLineMutex);
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
} // end of "defineTasksLine"



/*
  Function:
   
  Description:

  Input:

  Output
   'NONE
*/
const std::string& TasksWindow::getTasksLine()
{
  return m_tasksLine;
} // end of "getTasksLine"



/*
  Function:
   setTasksLine
   
  Description:

  Input:

  Output
   'NONE
*/
void TasksWindow::setTasksLine(const std::string& tasksLine)
{
  m_tasksLine = tasksLine;
} // end of "setTasksLine"
