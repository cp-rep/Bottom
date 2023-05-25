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
		const short& startY = 0,
		const short& startX = 0);

  // member functions
  void fixCOMMANDWinName();
  
private:
};


#endif
