/*
  File: topWindow.hpp
  Description:
*/
#ifndef TOPWINDOW_HPP
#define TOPWINDOW_HPP
#include "cursesWindow.hpp"

class TopWindow : public CursesWindow {
 public:
  // constructors
  TopWindow(std::string windowName = "",	      
	    const short& numLines = 0,
	    const short& numCols = 0,
	    const short& startY = 0,
	    const short& startX = 0);
  // getters
  const std::string& getUptime();
  
  // setters
  void setUptime(const std::string& uptime);

 private:
  // member data
  std::string m_uptime;
};


#endif
