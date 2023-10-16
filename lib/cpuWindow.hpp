/*
  File: 
   cpuWindow.hpp
  
  Description:
   Represents the %CPU(s) window of the Top program for the output line
   "%CPU(s): - X.X us, X.X sy, X.X ni..."
   
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

  void defineCPULine(const std::string& avgUs,
		     const std::string& avgSy,
		     const std::string& avgNi,
		     const std::string& avgId,
		     const std::string& avgWa,
		     const std::string& avgSt)
  {
    m_cpuLine = "%CPU(s): ";
    m_cpuLine.append(avgUs);
    m_cpuLine.append(" us, ");
    m_cpuLine.append(avgSy);
    m_cpuLine.append(" sy, ");
    m_cpuLine.append(avgNi);
    m_cpuLine.append(" ni, ");
    m_cpuLine.append(avgId);
    m_cpuLine.append(" id, ");
    m_cpuLine.append(avgWa);
    m_cpuLine.append(" wa, ");
    m_cpuLine.append("N/A");
    m_cpuLine.append(" si, ");
    m_cpuLine.append(avgSt);
    m_cpuLine.append(" st, ");
  }
  
  const std::string& getCPULine() { return m_cpuLine; }
  void setCPULine(const std::string& cpuLine) { m_cpuLine = cpuLine; };
  
private:
  std::string m_cpuLine;
};


#endif
