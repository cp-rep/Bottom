/*
  File: memWindow.cpp
  Description:
 */
#include "memWindow.hpp"



MemWindow::MemWindow(WINDOW* win,
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
} // end of "MemWindow Default Constructor"



void MemWindow::setStringMiB(const std::string& memTotal,
			     const std::string& memFree,
			     const std::string& memUsed,
			     const std::string& buffCache)
{
  m_MiB.clear();
  m_MiB.append("MiB Mem: ");
  m_MiB.append(memTotal);
  m_MiB.append(" total, ");
  m_MiB.append(memFree);
  m_MiB.append(" free, ");
  m_MiB.append(memUsed);
  m_MiB.append(" used, ");
  m_MiB.append(buffCache);
  m_MiB.append(" buff/cache");
} // end of "setMiB"


void MemWindow::setStringSwap(const std::string& swapTotal,
			      const std::string& swapFree,
			      const std::string& swapUsed,
			      const std::string& memAvailable)
{
  m_swap.clear();
  m_swap.append("MiB Swap: ");
  m_swap.append(swapTotal);
  m_swap.append(" total, ");
  m_swap.append(swapFree);
  m_swap.append(" free, ");
  m_swap.append(swapUsed);
  m_swap.append(" used, ");
  m_swap.append(memAvailable);
  m_swap.append(" avail/mem");

} // end of "setStringSwap"



