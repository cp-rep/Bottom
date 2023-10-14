/*
  File: topWindow.hpp

  Description:
   Represents the very top window of the Top program for the output line
   "top - xx:xx:xx up XX:XX, X users, load average: xxxx, xxxx, xxxx"
*/
#ifndef TOPWINDOW_HPP
#define TOPWINDOW_HPP
#include "cursesWindow.hpp"

class TopWindow : public CursesWindow {
 public:
  // constructors
  TopWindow(WINDOW* win = nullptr,
	    const std::string windowName = "",	      
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
