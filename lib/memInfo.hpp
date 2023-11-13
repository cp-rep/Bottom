/*
  File: memInfo.hpp
  
  Description:
  The MemInfo class is used to store data read from the
  "/proc/meminfo" file.
 */
#ifndef MEMINFO_HPP
#define MEMINFO_HPP

class MemInfo {
public:
  // constructors
  MemInfo(const int& memTotal = 0,
	  const int& memFree = 0,
	  const int& memUsed = 0,
	  const int& buffers = 0,
	  const int& cached = 0,
	  const int& buffCache = 0,
	  const int& sreclaimable = 0,
	  const int& swapTotal = 0,
	  const int& swapFree = 0,
	  const int& swapUsed = 0,
	  const int& memAvailable = 0);
  
  // member functions
  const int calculateBuffCache() const;
  const int calculateMemUsed() const;
  const int calculateSwapUsed() const;

  // getters
  const int& getMemTotal() const { return m_memTotal; }
  const int& getMemFree() const { return m_memFree; }
  const int& getMemUsed() const { return m_memUsed; }
  const int& getBuffers() const { return m_buffers; }
  const int& getCached() const { return m_cached; }
  const int& getBuffCache() const { return m_buffCache; }
  const int& getSReclaimable() const { return m_sreclaimable; }
  const int& getSwapTotal() const { return m_swapTotal; }
  const int& getSwapFree() const { return m_swapFree; }
  const int& getSwapUsed() const { return m_swapUsed; }
  const int& getMemAvailable() const { return m_memAvailable; }

  // setters
  void setMemTotal(const int& memTotal) { m_memTotal = memTotal; }
  void setMemFree(const int& memFree) { m_memFree = memFree; }
  void setMemUsed(const int& memUsed) { m_memUsed = memUsed; }
  void setBuffers(const int& buffers) { m_buffers = buffers; }
  void setCached(const int& cached) { m_cached = cached; }
  void setBuffCache(const int& buffCache) { m_buffCache = buffCache; }
  void setSReclaimable(const int& sreclaimable) { m_sreclaimable = sreclaimable; }
  void setSwapTotal(const int& swapTotal) { m_swapTotal = swapTotal; }
  void setSwapFree(const int& swapFree) { m_swapFree = swapFree; }
  void setSwapUsed(const int& swapUsed) { m_swapUsed = swapUsed; }
  void setMemAvailable(const int& memAvailable) { m_memAvailable = memAvailable; }
  
private:
  // member variables
  int m_memTotal;
  int m_memFree;
  int m_memUsed;  
  int m_buffers;
  int m_cached;
  int m_buffCache;
  int m_sreclaimable;
  int m_swapTotal;
  int m_swapFree;
  int m_swapUsed;
  int m_memAvailable;
};
#endif
