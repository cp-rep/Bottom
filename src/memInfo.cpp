/*
  File: memInfo.cpp
  Description:
 */
#include "memInfo.hpp"


MemInfo::MemInfo(const float& memTotal,
		 const float& memFree,
		 const float& buffers,
		 const float& cached,
		 const float& sreclaimable,
		 const float& swapTotal,
		 const float& swapFree,
		 const float& swapUsed,
		 const float& memAvailable)
{
  m_memTotal = memTotal;
  m_memFree = memFree;
  m_buffers = buffers;
  m_cached = cached;
  m_sreclaimable = sreclaimable;
  m_swapTotal = swapTotal;
  m_swapFree = swapFree;
  m_swapUsed = swapUsed;
  m_memAvailable = memAvailable;
}
