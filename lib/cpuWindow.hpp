/*
  File: 
   cpuWindow.hpp
  
  Description:
   The class definition for the CpuWindow class.
  
   Represents the %CPU(s) window of the Top program for the output line
   "%CPU(s): - X.X us, X.X sy, X.X ni..."
   
*/
#ifndef CPUWINDOW_HPP
#define CPUWINDOW_HPP
#include "cursesWindow.hpp"

class CpuWindow : public CursesWindow {
public:
  CpuWindow(WINDOW* win = nullptr,
	    const std::string& windowName = "",	      
	    const short& numLines = 0,
	    const short& numCols = 0,
	    const short& startY = 0,
	    const short& startX = 0);

  void defineCPULine(const std::string& avgUs,
		     const std::string& avgSy,
		     const std::string& avgNi,
		     const std::string& avgId,
		     const std::string& avgWa,
		     const std::string& avgSt);

  const std::string& getCPULine();
  void setCPULine(const std::string& cpuLine);
  
private:
  std::string m_cpuLine;
};


#endif
