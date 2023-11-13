/*
  File: memInfo.cpp
  
  Description:
   The class implementation for the MemInfo class.
 */
#include "memInfo.hpp"
#include <algorithm>



/*
  Function:
   MemInfo Constructor
  
  Description:
   The class constructor for constructing MemInfo objects and
   initializing related class data.

  Input:
   memTotal             - The total amount of main memory available to the OS.

   memFree              - The total amount of main memory not in use by the
                          OS.
			  
   buffers              - The total amount of main memory in use by the OS.

   cached               - Cached memory readily available to the OS that improve
                          operation speed when utilized.

   sreclaimable         - The amount of allocated by teh Slab that is currently
                          reclaimable.
			  
   swapTotal            - The total amount of swap memory available to the OS.

   swapFree             - The total amount of swap memory not in use by the OS.

   swapUsed             - The total amount of swap memory being used by the OS.

   memAvailable         - The amount of memory that is available to the OS.
                          for allocating new or existing processes.

  Output:
   NONE
*/
MemInfo::MemInfo(const int& memTotal,
		 const int& memFree,
		 const int& memUsed,
		 const int& buffers,
		 const int& cached,
		 const int& buffCache,
		 const int& sreclaimable,
		 const int& swapTotal,
		 const int& swapFree,
		 const int& swapUsed,
		 const int& memAvailable)
{
  setMemTotal(memTotal);
  setMemFree(memFree);
  setMemUsed(memUsed);
  setBuffers(buffers);
  setCached(cached);
  setBuffCache(buffCache);
  setSReclaimable(sreclaimable);
  setSwapTotal(swapTotal);
  setSwapFree(swapFree);
  setSwapUsed(swapUsed);
  setMemAvailable(memAvailable);
} // end of "MemInfo Constructor"



/*
  Function:
   calculateBuffCache

  Description:
   Calculates and returns the "buff/cache" value as seen in the top
   program in the "MiB Mem" section.

  Input:
   NONE

  Output:
  const int             - The resulting calculation.
*/
const int MemInfo::calculateBuffCache() const
{
  const int tempBuffers = getBuffers();
  const int tempCached = getCached();
  const int tempSReclaimable = getSReclaimable();
  return tempBuffers + tempCached + tempSReclaimable;
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
   const int            - The result of the calculation.
*/
const int MemInfo::calculateMemUsed() const
{
  return getMemTotal() - (getMemFree() + getBuffCache());
} // end of "calculateMemUsed"



/*
  Function:
   calculateSwapUsed

  Description:
   Calculates the how much of swap memory is currently in use.

  Input:
   NONE

  Output:
   const int            - The result of the calculation.
*/
const int MemInfo::calculateSwapUsed() const
{
  return getSwapTotal() - getSwapFree();
} // end of "calculateSwapUsed"
