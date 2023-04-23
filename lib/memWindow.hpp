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
	    const float memTotal = 0,
	    const float memFree = 0,
	    const float memUsed = 0,
	    const float buffCache = 0,
	    const float swapTotal = 0,
	    const float swapFree = 0,
	    const float swapUsed = 0,
	    const float swapAvailable = 0);

  // member functions
  const std::string returnLineWithPhrase(const std::string& phrase);
  int defineMemData();

  // getters
  const float& getMemTotal() { return m_memTotal; }


  // setters
  void setMemTotal(const int& memTotal);
  

  // helper functions
  const int parseIntFromLine(const std::string& line);
  
private:
  std::string m_MiB;
  std::string m_swap;
  float m_memTotal;
  float m_memFree;
  float m_memUsed;
  float m_buffCache;
  float m_swapTotal;
  float m_swapFree;
  float m_swapUsed;
  float m_swapAvailable;
};

#endif
