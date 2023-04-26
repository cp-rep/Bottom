/*
  File: memInfo.cpp
  
  Description:
  The MemInfo class function implementations from the
  memInfo.hpp header file.
 */
#include "memInfo.hpp"



/*
  Function:

  Description:
*/
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
} // end of "MemInfo Default Constructor"



/*
  Function:
  calculateBuffCache

  Description:
  Calculates and returns the "buff/cache" value as seen in the top
  program in the "MiB Mem" section.

  Input:
  NONE

  Output:
  const float           - an rvalue that is the result of the
                          buff/cache calculation.
*/
const float MemInfo::calculateBuffCache() const
{
  return m_buffers + m_cached + m_sreclaimable;
} // end of "calculateBuffCache"



/*
  Function:
  calcuteMemUsed
  
  Description:
  Calculates and returns the memory "used" as seen in the top program
  under the "MiB Mem" section.

  Input:
  NONE

  Output:
  const float            - an rvalue that is the result of the memory
                           "used" calculation.
*/
const float MemInfo::calculateMemUsed() const
{
  return m_memTotal - m_memFree - m_buffers - m_cached - m_sreclaimable;
} // end of "calculateMemUsed"



/*
  Function:
  calculateSwapUsed

  Description:
  Calculates the difference of the m_swapTotal and m_swapFree
  member variables and returns it.

  Input:
  NONE

  Output:
  NONE
*/
const float MemInfo::calculateSwapUsed(const int& swapTotal,
			  const int& swapFree) const
{
  return swapTotal - swapFree;
} // end of "calculateSwapUsed"



/*
  Function:
  m_memTotal
  
  Description:
  Returns the m_memTotal member variable.

  Input:
  NONE

  Output:
  m_memTotal             - a const reference to the m_memTotal
                           member variable
*/
const float& MemInfo::getMemTotal() const
{
  return m_memTotal;
} // end of "getMemTotal"



/*
  Function:
  getMemFree

  Description:
  Returns the m_memFree member variable.

  Input:
  NONE

  Output:  
  m_memFree              - a const reference to the m_memFree
                           member variable.
*/
const float& MemInfo::getMemFree() const
{
  return m_memFree;
} // end of "getMemFree"



/*
  Function:
  getBuffers
  

  Description:
  Returns the m_buffers member variable.

  Input:
  NONE

  Output:  
  m_buffers              - a const reference to the m_buffers
                           member variable.  
*/
const float& MemInfo::getBuffers() const
{
  return m_buffers;
} // end of "getBuffers"



/*
  Function:
  getCached

  Description:
  Returns the m_cached member variable.

  Input:
  NONE

  Output:  
  m_cached               - a const reference to the m_cached
                           member variable.  
*/
const float& MemInfo::getCached() const
{
  return m_cached;
} // end of "getCached"



/*
  Function:
  getSwapTotal

  Description:
  Returns the m_swapTotal member variable.

  Input:
  NONE

  Output:  
  m_swapTotal            - a const reference to the m_swapTotal
                           member variable.  
*/
const float& MemInfo::getSwapTotal() const
{
  return m_swapTotal;
} // end of "getSwapTotal"



/*
  Function:
  getSwapFree

  Description:
  Returns the m_swapFree member variable.

  Input:
  NONE

  Output:  
  m_swapFree             - a const reference to the m_swapFree
                           member variable.  
*/
const float& MemInfo::getSwapFree() const
{
  return m_swapFree;
} // end of "getSwapFree"



/*
  Function:
  getSwapUsed

  Description:
  Returns the m_swapUsed member variable.

  Input:
  NONE

  Output:
  m_swapUsed             - a const reference to the m_swapUsed
                           member variable.  
*/
const float& MemInfo::getSwapUsed() const
{
  return m_swapUsed;
} // end of "getSwapUsed"



/*
  Function:
  getMemAvailable

  Description:
  Returns the m_memAvailable member variable.

  Input:
  NONE

  Output:
  m_memAvailable         - a const reference to the m_memAvailable
                           member variable.  
*/
const float& MemInfo::getMemAvailable() const
{
  return m_memAvailable;
} // end of "getMemAvailable"



/*
  Function:
  setMemTotal

  Description:
  Sets the m_memTotal member variable.

  Input:
  NONE

  Output:
  NONE
*/
void MemInfo::setMemTotal(const int& memTotal)
{
  m_memTotal = memTotal;
} // end of "setMemTotal"



/*
  Function:
  setMemFree

  Description:
  Sets the m_memFree member variable.

  Input:
  NONE

  Output:
  NONE
*/
void MemInfo::setMemFree(const int& memFree)
{
  m_memFree = memFree;
} // end of "setMemFree"



/*
  Function:
  setBuffers

  Description:
  Sets the m_buffers member variable.

  Input:
  NONE

  Output:
  NONE
*/
void MemInfo::setBuffers(const int& buffers)
{
  m_buffers = buffers;
} // end of "setBuffers"



/*
  Function:
  setCached

  Description:
  Sets the m_cached member variable.

  Input:
  NONE

  Output:
  NONE
*/
void MemInfo::setCached(const int& cached)
{
  m_cached = cached;
} // end of "setCached"



/*
  Function:
  setSReclaimable

  Description:
  Sets the m_sreclaimable member variable.

  Input:
  NONE

  Output:
  NONE
*/
void MemInfo::setSReclaimable(const int& sreclaimable)
{
  m_sreclaimable = sreclaimable;
} // end of "setSReclaimable"



/*
  Function:
  setSwapTotal

  Description:
  Sets the m_swapTotal member variable.

  Input:
  NONE

  Output:
  NONE
*/
void MemInfo::setSwapTotal(const int& swapTotal)
{
  m_swapTotal = swapTotal;
} // end of "setSwapTotal"



/*
  Function:
  setSwapFree

  Description:
  Sets the m_swapFree member variable.

  Input:
  NONE

  Output:
  NONE
*/
void MemInfo::setSwapFree(const int& swapFree)
{
  m_swapFree = swapFree;
} // end of "setSwapFree"



/*
  Function:
  setMemAvailable

  Description:
  Sets the m_memAvailable member variable.

  Input:
  NONE

  Output:
  NONE
  
*/
void MemInfo::setMemAvailable(const int& memAvailable)
{
  m_memAvailable = memAvailable;
} // end of "setMemAvailable"
