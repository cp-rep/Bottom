/*
  File: memWindow.hpp
  Description:
 */
#ifndef MEMWINDOW_HPP
#define MEMWINDOW_HPP
#include "cursesWindow.hpp"



class MemWindow : public CursesWindow {
public:

  MemWindow(std::string windowName = "",	      
	    const short& numLines = 0,
	    const short& numCols = 0,
	    const short& maxWindowY  = 0,
	    const short& maxWindowX = 0,
	    const short& minWindowY = 0,
	    const short& minWindowX = 0,
	    const short& centerY = 0,
	    const short& centerX = 0,
	    const short& startY = 0,
	    const short& startX = 0,
	    const short& currentY = 0,
	    const short& currentX = 0,
	    const short& previousY =  0,
	    const short& previousX = 0,
	    const std::string& MiB = "",
	    const std::string& swap = "",
	    const float& memTotal = 0,
	    const float& memFree = 0,
	    const float& buffers = 0,
	    const float& cached = 0,
	    const float& sreclaimable = 0,
	    const float& swapTotal = 0,
	    const float& swapFree = 0,
	    const float& swapUsed = 0,
	    const float& memAvailable = 0);

  // member functions
  const float convertkBToKiB(const float& val);
  const float convertKiBToMiB();
  const float getBuffCache() const { return m_buffers + m_cached + m_sreclaimable; }
  const float getMemUsed() const { return m_memTotal - m_memFree -
                                    m_buffers - m_cached - m_sreclaimable; }  
  
  // getters
  const std::string& getMiB() const { return m_MiB; }
  const std::string& getSwap() const { return m_swap; }  
  const float& getMemTotal() const { return m_memTotal; }
  const float& getMemFree() const { return m_memFree; }
  const float& getBuffers() const { return m_buffers; }
  const float& getCached() const { return m_cached; }
  const float& getSwapTotal() const { return m_swapTotal; }
  const float& getSwapFree() const { return m_swapFree; }
  const float& getSwapUsed() const { return m_swapUsed; }
  const float& getMemAvailable() const { return m_memAvailable; }

  // setters
  void setStringMiB();
  void setStringSwap();  
  void setMemTotal(const int& memTotal) { m_memTotal = memTotal; }
  void setMemFree(const int& memFree) { m_memFree = memFree; }
  void setBuffers(const int& buffers) { m_buffers = buffers; }
  void setCached(const int& cached) { m_cached = cached; }
  void setSReclaimable(const int& sreclaimable) { m_sreclaimable = sreclaimable; }
  void setSwapTotal(const int& swapTotal) { m_swapTotal = swapTotal; }
  void setSwapFree(const int& swapFree) { m_swapFree = swapFree; }
  void setSwapUsed(const int& swapTotal,
		   const int& swapFree) { m_swapUsed = swapTotal - swapFree; }
  void setMemAvailable(const int& memAvailable) { m_memAvailable = memAvailable; }

private:
  std::string m_MiB;
  std::string m_swap;
  float m_memTotal;
  float m_memFree;
  float m_buffers;
  float m_cached;
  float m_sreclaimable;
  float m_swapTotal;
  float m_swapFree;
  float m_swapUsed;
  float m_memAvailable;
};

#endif
