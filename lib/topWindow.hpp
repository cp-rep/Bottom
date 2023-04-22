/*
  File: topWindow.hpp
  Description:
*/
#ifndef TOPWINDOW_HPP
#define TOPWINDOW_HPP
#include "cursesWindow.hpp"

class TopWindow : public CursesWindow {
 public:
  TopWindow(std::string windowName = "",	      
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
	    struct tm* timeinfo = nullptr);

  // member functions
  const std::string& getUptime();
  void drawTop();

 private:
  // member data
  std::string m_uptime;
};


#endif
