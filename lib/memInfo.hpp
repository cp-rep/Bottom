/*
  File: memInfo.hpp
  Description:
 */
#ifndef MEMINFO_HPP
#define MEMINFO_HPP

class MemInfo {
public:
  // constructors
  MemInfo(const float& memTotal = 0,
	  const float& memFree = 0,
	  const float& buffers = 0,
	  const float& cached = 0,
	  const float& sreclaimable = 0,
	  const float& swapTotal = 0,
	  const float& swapFree = 0,
	  const float& swapUsed = 0,
	  const float& memAvailable = 0);
  
  // member functions
  const float calculateBuffCache() const { return m_buffers + m_cached + m_sreclaimable; }
  const float calculateMemUsed() const { return m_memTotal - m_memFree -
      m_buffers - m_cached - m_sreclaimable; }  
  
  // getters
  const float& getMemTotal() const { return m_memTotal; }
  const float& getMemFree() const { return m_memFree; }
  const float& getBuffers() const { return m_buffers; }
  const float& getCached() const { return m_cached; }
  const float& getSwapTotal() const { return m_swapTotal; }
  const float& getSwapFree() const { return m_swapFree; }
  const float& getSwapUsed() const { return m_swapUsed; }
  const float& getMemAvailable() const { return m_memAvailable; }

  // setters
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
  // member variables
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
