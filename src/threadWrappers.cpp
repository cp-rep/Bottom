/*
  File:
   threadWrappers.cpp
  
  Description:
*/
#include "threadWrappers.hpp"

void extractProcStatThreadWrapper(CPUInfo& cpuInfo,
				  const std::string& filePath,
				  void (*func)(CPUInfo&, const std::string&),
				  const CPUInfo& cpuInfoStart,
				  const CPUInfo& cpuInfoEnd,
				  CPUUsage (*func1)(const CPUInfo&, const CPUInfo&),
				  CPUUsage& cpuUsage)
			    
			      
{
  func(cpuInfo, filePath);
  cpuUsage = func1(cpuInfoStart,
		   cpuInfoEnd);
}
