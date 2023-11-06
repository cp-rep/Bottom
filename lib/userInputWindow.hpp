/*
  File: 
   userInputWindow.hpp

  Description:
   The class definition for the UserInputWindow class.
*/
#ifndef USERINPUTWINDOW_HPP
#define USERINPUTWINDOW_HPP
#include "cursesWindow.hpp"

class UserInputWindow : public CursesWindow {
public:
  UserInputWindow(WINDOW* win = nullptr,
		  const std::string& windowName = "",
		  const short& numLines = 0,
		  const short& numCols = 0,
		  const short& startY = 0,
		  const short& startX = 0);
private:
};

#endif
