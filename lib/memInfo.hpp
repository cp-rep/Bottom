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
  const int& getMemTotal() const;
  const int& getMemFree() const;
  const int& getMemUsed() const {  return m_memUsed; }
  const int& getBuffers() const;
  const int& getCached() const;
  const int& getBuffCache() const;
  const int& getSwapTotal() const;
  const int& getSwapFree() const;
  const int& getSwapUsed() const;
  const int& getMemAvailable() const;

  // setters
  void setMemTotal(const int& memTotal);
  void setMemFree(const int& memFree);
  void setMemUsed(const int& memUsed){ m_memUsed = memUsed; }
  void setBuffers(const int& buffers);
  void setCached(const int& cached);
  void setBuffCache(const int& buffCache);  
  void setSReclaimable(const int& sreclaimable);
  void setSwapTotal(const int& swapTotal);
  void setSwapFree(const int& swapFree);
  void setSwapUsed(const int& swapUsed){ m_swapUsed = swapUsed;}
  void setMemAvailable(const int& memAvailable);
  
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
