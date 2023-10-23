/*
  File: cpuWindow.cpp
  Description:
 */
#include "cpuWindow.hpp"



/*
  Function
   Function Constructor

  Description:
   The class constructor for creating a CpuWindow object initializing related 
   private member data.

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
   None
*/
CpuWindow::CpuWindow(WINDOW* win,
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
} // end of "CpuWindow Constructor'



/*
  Function:
  
  Description:

  Input:

  Output:

*/
void CpuWindow::defineCPULine(const std::string& avgUs,
			      const std::string& avgSy,
			      const std::string& avgNi,
			      const std::string& avgId,
			      const std::string& avgWa,
			      const std::string& avgSt)
{
  m_cpuLine = "%CPU(s): ";
  m_cpuLine.append(avgUs);
  m_cpuLine.append(" us, ");
  m_cpuLine.append(avgSy);
  m_cpuLine.append(" sy, ");
  m_cpuLine.append(avgNi);
  m_cpuLine.append(" ni, ");
  m_cpuLine.append(avgId);
  m_cpuLine.append(" id, ");
  m_cpuLine.append(avgWa);
  m_cpuLine.append(" wa, ");
  m_cpuLine.append("N/A");
  m_cpuLine.append(" si, ");
  m_cpuLine.append(avgSt);
  m_cpuLine.append(" st, ");
} // end of "defineCPULine"



/*
  Function:
  
  Description:

  Input:

  Output:

*/
const std::string& CpuWindow::getCPULine()
{
  return m_cpuLine;
} // end of "getCPULine"



/*
  Function:
  
  Description:

  Input:

  Output:
*/
void CpuWindow::setCPULine(const std::string& cpuLine)
{
  m_cpuLine = cpuLine;
} // end of "setCPULine"
