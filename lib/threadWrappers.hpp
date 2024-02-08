/*
  File:
   threadWrappers.cpp
  
  Description:
*/
#ifndef THREADWRAPPERS_HPP
#define THREADWRAPPERS_HPP
#include <string>
#include "cpuInfo.hpp"

void extractProcStatThreadWrapper(CPUInfo& cpuInfo,
				  const std::string& filePath,
				  void (*func)(CPUInfo&, const std::string&),
				  const CPUInfo& cpuInfoStart,
				  const CPUInfo& cpuInfoEnd,
				  CPUUsage (*func1)(const CPUInfo&, const CPUInfo&),
				  CPUUsage& cpuUsage);

#endif
