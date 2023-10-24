/*
  File: memWindow.hpp
  Description:
 */
#ifndef MEMWINDOW_HPP
#define MEMWINDOW_HPP
#include "cursesWindow.hpp"

class MemWindow : public CursesWindow {
public:
  // constructors
  MemWindow(WINDOW* win = nullptr,
	    const std::string& windowName = "",	      
	    const short& numLines = 0,
	    const short& numCols = 0,
	    const short& startY = 0,
	    const short& startX = 0);

  // getters
  const std::string& getMiB() const;
  const std::string& getSwap() const;
  
  // setters
  void setStringMiB();
  void setStringSwap();
		     
		     
		     
private:
  std::string m_MiB;
  std::string m_swap;
};

#endif
