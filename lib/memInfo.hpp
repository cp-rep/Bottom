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
  const float calculateBuffCache() const;
  const float calculateMemUsed() const;
  const float calculateSwapUsed() const;
				
  
  // getters
  const float& getMemTotal() const;
  const float& getMemFree() const;
  const float& getBuffers() const;
  const float& getCached() const;
  const float& getSwapTotal() const;
  const float& getSwapFree() const;
  const float& getSwapUsed() const;
  const float& getMemAvailable() const;

  // setters
  void setMemTotal(const int& memTotal);
  void setMemFree(const int& memFree);
  void setBuffers(const int& buffers);
  void setCached(const int& cached);
  void setSReclaimable(const int& sreclaimable);
  void setSwapTotal(const int& swapTotal);
  void setSwapFree(const int& swapFree);
  void setSwapUsed(const int& swapTotal,
		   const int& swapFree);
  void setMemAvailable(const int& memAvailable);
  
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
