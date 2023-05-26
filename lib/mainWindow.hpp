/*
  File: mainWindow.hpp
  Description:
 */
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include "cursesWindow.hpp"

class MainWindow : public CursesWindow {
public:
  MainWindow(WINDOW* win = nullptr,
	     const std::string windowName = "",	      
	     const short& numLines = 0,
	     const short& numCols = 0,
	     const short& startY = 0,
	     const short& startX = 0);
private:
};

#endif
