/*
  File: cpuWindow.hpp
  Description:
 */
#ifndef CPUWINDOW_HPP
#define CPUWINDOW_HPP
#include "cursesWindow.hpp"

class CpuWindow : public CursesWindow {
public:
  CpuWindow(WINDOW* win = nullptr,
	    const std::string windowName = "",	      
	    const short& numLines = 0,
	    const short& numCols = 0,
	    const short& startY = 0,
	    const short& startX = 0);

  //  const std::string& getCPULine();

  //  void setCPULine(const std::string& cpuLine) { m_cpuLine = cpuLine; };
  
private:
  //  std::string m_cpuLine;
};


#endif
