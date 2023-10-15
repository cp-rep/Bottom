/*
  File: 
   topWindow.cpp

  Description:
   The implementation of the topWindow.hpp class functions.
*/
#include "topWindow.hpp"



/*
  Function:
   TopWindow Default Constructor
   
  Description:

  Input:

  Output:
  NONE
*/
TopWindow::TopWindow(WINDOW* win,
		     const std::string windowName,	      
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
  m_topLine = "";
} // end of "TopWindow Default Constructor"



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
   NONE

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
   NONE

  Output:
   NONE
*/
void TopWindow::defineTopLine(const std::string& HHMMSS,
			      const int& numDays,
			      const int& numHours,
			      const int& numMinutes,
			      const std::vector<std::string> parsedLoadAvg)
{
  m_topLine.clear();
  m_topLine.append("top -");
  m_topLine.append(HHMMSS);
  
  
  if(numDays == 1)
    {
      m_topLine.append(std::to_string(numDays));
      m_topLine.append(" day, ");
    }
  else
    {
      m_topLine.append(std::to_string(numDays));      
      m_topLine.append(" days, ");
    }

    m_topLine.append(std::to_string(numHours));
    m_topLine.append(":");
    m_topLine.append(std::to_string(numMinutes));
    m_topLine.append(", ");
    m_topLine.append("0");
    m_topLine.append(" users, load average: ");
    m_topLine.append(parsedLoadAvg.at(0));
    m_topLine.append(" ");
    m_topLine.append(parsedLoadAvg.at(1));
    m_topLine.append(" ");
    m_topLine.append(parsedLoadAvg.at(2));
} // end of "defineTopLine"
