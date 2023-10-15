/*
  File: percentCPUWindow.hpp
  Description:
 */
#ifndef PERCENTCPUWINDOW_HPP
#define PERCENTCPUWINDOW_HPP
#include "cursesWindow.hpp"

class PercentCPUWindow : public CursesWindow {
public:
  PercentCPUWindow(WINDOW* win = nullptr,
		   const std::string windowName = "",
		   const short& numLines = 0,
		   const short& numCols = 0,
		   const short& startY = 0,
		   const short& startX = 0);

  const std::string getPercentCPULine();
  void setPercentCPULine();
  
private:
  std::string percentCPULine;
};

#endif
