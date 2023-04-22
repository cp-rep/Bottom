/*
  File: memWindow.hpp
  Description:
 */
#ifndef MEMWINDOW_HPP
#define MEMWINDOW_HPP
#include "cursesWindow.hpp"



class MemWindow : public CursesWindow {
public:

  MemWindow(std::string windowName = "",	      
	    const short& numLines = 0,
	    const short& numCols = 0,
	    const short& maxWindowY  = 0,
	    const short& maxWindowX = 0,
	    const short& minWindowY = 0,
	    const short& minWindowX = 0,
	    const short& centerY = 0,
	    const short& centerX = 0,
	    const short& startY = 0,
	    const short& startX = 0,
	    const short& currentY = 0,
	    const short& currentX = 0,
	    const short& previousY =  0,
	    const short& previousX = 0,
	    const std::string& MiB = "",
	    const std::string& swap = "",
	    const int memTotal = 0,
	    const int memFree = 0,
	    const int memUsed = 0,
	    const int buffCache = 0,
	    const int swapTotal = 0,
	    const int swapFree = 0,
	    const int swapUsed = 0,
	    const int swapAvailable = 0);

  // member functions
  const std::string readMiBTotal();
  
private:
  std::string m_MiB;
  std::string m_swap;
  int m_memTotal;
  int m_memFree;
  int m_memUsed;
  int m_buffCache;
  int m_swapTotal;
  int m_swapFree;
  int m_swapUsed;
  int m_swapAvailable;
};

#endif
