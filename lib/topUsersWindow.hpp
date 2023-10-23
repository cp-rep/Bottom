/*
  File:
   topUsersWindow.hpp
   
  Description:
   The class definition for the topUsersWindow class.
 */
#ifndef TOPUSERSWINDOW_HPP
#define TOPUSERSWINDOW_HPP
#include "cursesWindow.hpp"

class TopUsersWindow : public CursesWindow {
public:

  TopUsersWindow(WINDOW* win = nullptr,
		 const std::string windowName = "",	      
		 const short& numLines = 0,
		 const short& numCols = 0,
		 const short& startY = 0,
		 const short& startX = 0);
private:
};


#endif
