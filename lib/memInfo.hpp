/*
  File: memInfo.hpp
  
  Description:
  The MemInfo class is used to store data read from the
  "/proc/meminfo" file.
 */
#ifndef MEMINFO_HPP
#define MEMINFO_HPP
#include <mutex>

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
  void setMemTotal(const int& memTotal) {
    std::lock_guard<std::mutex> lock(m_memTotalMut);
    m_memTotal = memTotal; }
  void setMemFree(const int& memFree) {
    std::lock_guard<std::mutex> lock(m_memFreeMut);
    m_memFree = memFree; }
  void setMemUsed(const int& memUsed) {
    std::lock_guard<std::mutex> lock(m_memUsedMut);
    m_memUsed = memUsed; }
  void setBuffers(const int& buffers) {
    std::lock_guard<std::mutex> lock(m_buffersMut);
    m_buffers = buffers; }
  void setCached(const int& cached) {
    std::lock_guard<std::mutex> lock(m_cachedMut);
    m_cached = cached; }
  void setBuffCache(const int& buffCache) {
    std::lock_guard<std::mutex> lock(m_buffCacheMut);
    m_buffCache = buffCache; }
  void setSReclaimable(const int& sreclaimable) {
    std::lock_guard<std::mutex> lock(m_sreclaimableMut);
    m_sreclaimable = sreclaimable; }
  void setSwapTotal(const int& swapTotal) {
    std::lock_guard<std::mutex> lock(m_swapTotalMut);
    m_swapTotal = swapTotal; }
  void setSwapFree(const int& swapFree) {
    std::lock_guard<std::mutex> lock(m_swapFreeMut);
    m_swapFree = swapFree; }
  void setSwapUsed(const int& swapUsed) {
    std::lock_guard<std::mutex> lock(m_swapUsedMut);
    m_swapUsed = swapUsed; }
  void setMemAvailable(const int& memAvailable) {
    std::lock_guard<std::mutex> lock(m_memAvailableMut);
    m_memAvailable = memAvailable; }
  
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

  mutable std::mutex m_memTotalMut;
  mutable std::mutex m_memFreeMut;
  mutable std::mutex m_memUsedMut;
  mutable std::mutex m_buffersMut;
  mutable std::mutex m_cachedMut;
  mutable std::mutex m_buffCacheMut;
  mutable std::mutex m_sreclaimableMut;
  mutable std::mutex m_swapTotalMut;
  mutable std::mutex m_swapFreeMut;
  mutable std::mutex m_swapUsedMut;
  mutable std::mutex m_memAvailableMut;
};
#endif
