/*
  File: 
   topWindow.cpp

  Description:
   Class implementation for the TopWindow class.
*/
#include "topWindow.hpp"
#include <iostream>



/*
  Function:
   TopWindow Constructor
   
  Description:
   The class constructor for creating TopWindow objects and 
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
TopWindow::TopWindow(WINDOW* win,
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
  setTopLine("");
} // end of "TopWindow Constructor"



/*
  Function:
   getTopLine

  Description:
   Returns the m_topLine member variable.

  Input:
   NONE

  Output:
   m_topLine               - a const reference to the m_topLine
                             member variable.
*/
const std::string& TopWindow::getTopLine()
{
  return m_topLine;
} // end of "getTopLine"



/*
  Function:
   setTopLine

  Description:
   Defines the m_topLine member variable with the incoming string parameter.

  Input:
   topLine              - a const string reference that is used to set
                          the calling object's member data.

  Output:
   NONE
*/
void TopWindow::setTopLine(const std::string& topLine)
{
  m_topLine = topLine;
} // end of "setTopLine"



/*
  Function:
   defineTopLine

  Description:
   Clears and defines the m_topLine member variable.

  Input:
   HHMMSS               - a const string reference to the hours, minutes, and
                          seconds to be appended to topWindow's output line.
   
   numDays              - a const int reference to the number of days the
                          computer has been running to be appended to
                          topWindow's output line.
     
 
   numHours             - a const int reference to the number of hours the
                          computer has been running to be appended to
                          topWindow's output line.

   numMinutes           - a const int reference to the number of minutes the
                          computer has been running to be appended to
                          topWindow's output line.

   parsedLoadAvg        - a reference to a const vector of string objects
                          that contained the computer's parsed current load
                          average.
  Output:
   NONE
*/
void TopWindow::defineTopLine(const std::string& HHMMSS,
			      const int& numDays,
			      const int& numHours,
			      const int& numMinutes,
			      const std::vector<std::string>& parsedLoadAvg)
{
  std::lock_guard<std::mutex> lock(m_topLineMutex);
  m_topLine.clear();
  m_topLine.append("top - ");
  m_topLine.append(HHMMSS);
  m_topLine.append(" up ");

  if(numDays < 1)
    {
      if(numHours < 1)
	{
	  m_topLine.append(std::to_string(numMinutes));
	  m_topLine.append(" min, ");
	}
      else
	{
	  m_topLine.append(std::to_string(numHours));
	  m_topLine.append(":"); 
	  if(numMinutes < 10)
	    {
	      m_topLine.append("0");
	    }
	  m_topLine.append(std::to_string(numMinutes));
	  m_topLine.append(", ");

	}
    }
  else if(numDays == 1)
    {
      m_topLine.append(std::to_string(numDays));
      m_topLine.append(" day, ");
    }
  else
    {
      m_topLine.append(std::to_string(numDays));      
      m_topLine.append(" days, ");
    }
    m_topLine.append("0");
    m_topLine.append(" users, load average: ");
    m_topLine.append(parsedLoadAvg.at(0));
    m_topLine.append(" ");
    m_topLine.append(parsedLoadAvg.at(1));
    m_topLine.append(" ");
    m_topLine.append(parsedLoadAvg.at(2));
} // end of "defineTopLine"
