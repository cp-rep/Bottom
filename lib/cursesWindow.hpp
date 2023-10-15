/*
  File: cursesWindow.hpp
  Description:
*/
#ifndef CURSESWINDOW_HPP
#define CURSESWINDOW_HPP
#include <curses.h>
#include <string>
#include <vector>

class CursesWindow {
public:
  // constructors
  CursesWindow(WINDOW* win = nullptr,
	       const std::string windowName = "",	      
	       const int& numLines = 0,
	       const int& numCols = 0,
	       const int& startY = 0,
	       const int& startX = 0);

  // destructor
  ~CursesWindow();

  // member functions
  void defineWindow(WINDOW* win,
		    const std::string windowName,
		    const int& numLines,
		    const int& numCols,
		    const int& startY,
		    const int& startX);
  void createWindow(const int& numLines,
		    const int& numCols,
		    const int& startY,
		    const int& startX);
  void deleteWindow();
  
  // getters
  WINDOW* getWindow();
  const std::string& getWindowName() const;
  const int& getNumCols() const;
  const int& getNumLines() const;
  const int& getStartY() const;
  const int& getStartX() const;
  
  // setters
  void setWindow(WINDOW* window);
  WINDOW* createWindow();
  void setWindowName(const std::string winName);
  void setNumLines(const int& numLines);
  void setNumCols(const int& numCols);
  void setStartY(const int& startY);
  void setStartX(const int& startX);

  // virtual functions
  // memWindow.hpp
  virtual void setStringMiB(const std::string& memTotal,
			    const std::string& memFree,
			    const std::string& memUsed,
			    const std::string& buffCache) {}
  virtual void setStringSwap(const std::string& swapTotal,
			     const std::string& swapFree,
			     const std::string& swapUsed,
			     const std::string& memAvailable) {}
  // cpuWindow.hpp
  virtual void defineCPULine(const std::string& avgUs,
			     const std::string& avgSy,
			     const std::string& avgNi,
			     const std::string& avgId,
			     const std::string& avgWa,
			     const std::string& avgSt){}
  virtual const std::string& getCPULine(){}
  virtual void setCPULine(const std::string& cpuLine){}

  // topWindow.hpp
  virtual void defineTopLine(const std::string& HHMMSS,
			     const int& numDays,
			     const int& numHours,
			     const int& numMinutes,
			     const std::vector<std::string> parsedLoadAvg) {}
  virtual const std::string& getTopLine() {}
  virtual void setTopLine(std::string& topLine) {}
  
private:
  // member variables
  WINDOW* m_window;
  std::string m_windowName;
  int m_numLines;
  int m_numCols;
  int m_startY;
  int m_startX;
};

#endif
