/*
  File: COMMANDWindow.hpp
  Description:
 */
#ifndef COMMANDWINDOW_HPP
#define COMMANDWINDOW_HPP

#include "cursesWindow.hpp"

class COMMANDWindow : public CursesWindow {
public:
  // default constructor
  COMMANDWindow(std::string windowName = "",	      
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
		const short& previousX = 0);

  // member functions
  void fixCOMMANDWinName();
  
private:
};


#endif
