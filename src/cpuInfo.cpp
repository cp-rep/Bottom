/*
  File:
   cpuInfo.cpp
  
  Description:
   The CPUInfo class function implementations from the cpuInfo.hpp header file.
 */
#include "cpuInfo.hpp"

#define _MAXPERCENT 100.0

/*
  Function:
   CPUInfo Constructor

  Description:
   Constructs CPUInfo objects.

  Input:
   us                   - A reference to a constant integer that should hold
                          the CPU time of user processes.

   ni                   - A reference to a constant integer that should hold
                          the CPU time spent on processes that have been niced.
			  
   sy                   - A reference to a constant integer that should hold
                          the CPU time of system processes.

   id                   - A reference to a constant integer that should hold
                          the CPU time spent idling.
			  
   wa                   - A reference to a constant integer that should hold
                          the CPU time spent waiting for IO operations to
			  complete.
			  
   irq                  - A reference to a constant integer that should hold
                          the CPU time spent handling hardware interrupts.

   sirq                 - A reference to a constant integer that should hold
                          the CPU time spent handling software interrupts.

   st                   - A reference to a constant integer that should hold
                          the time spent for a virtual CPU to be scheduled
			  on a physical CPU.

   gu                   - A reference to a constant integer that should hold
                          the CPU time spent running a virtual CPU for
			  guest operating systems.

   gu                   - A reference to a constant integer that should hold
                          the CPU time spent on nice guest tasks initiated
			  by a virtual machine.
  Output:
   NONE
 */
CPUInfo::CPUInfo(const unsigned int& us,
		 const unsigned int& ni,
		 const unsigned int& sy,
		 const unsigned int& id,
		 const unsigned int& wa,
		 const unsigned int& irq,
		 const unsigned int& sirq,
		 const unsigned int& st,
		 const unsigned int& gu,
		 const unsigned int& gun)
{
  setUs(us);
  setNi(ni);
  setSy(sy);
  setId(id);
  setWa(wa);
  setIrq(irq);
  setSirq(sirq);
  setSt(st);
  setGu(gu);
  setGun(gun);
} // end of "CPUInfo constructor"



/*
  Function:
   calcCPUUsage

  Description:

  Input:

  Output:
*/
CPUUsage calcCPUUsage(const CPUInfo& cpuInfoStart,
		      const CPUInfo& cpuInfoEnd)
{
  CPUUsage usage;
  unsigned long startIdle;
  unsigned long endIdle;
  unsigned long startNonIdle;
  unsigned long endNonIdle;
  unsigned long startTime;
  unsigned long endTime;
  unsigned long total;
  unsigned long idle;
  
  startIdle = cpuInfoStart.getId() + cpuInfoStart.getWa();
  endIdle = cpuInfoEnd.getId() + cpuInfoEnd.getWa();

  startNonIdle = cpuInfoStart.getUs() + cpuInfoStart.getNi() +
    cpuInfoStart.getSy() + cpuInfoStart.getIrq() + cpuInfoStart.getSirq() +
    cpuInfoStart.getSt();
  endNonIdle = cpuInfoEnd.getUs() + cpuInfoEnd.getNi() + cpuInfoEnd.getSy() +
    cpuInfoEnd.getIrq() + cpuInfoEnd.getSirq() + cpuInfoEnd.getSt();

  startTime = startIdle + startNonIdle;
  endTime = endIdle + endNonIdle;

  total = endTime - startTime;
  idle = endIdle - startIdle;

  usage.us = _MAXPERCENT * ((double) cpuInfoEnd.getUs() -
			    (double)cpuInfoStart.getUs()) / total;
  
  usage.ni = _MAXPERCENT * ((double)cpuInfoEnd.getNi() -
			    (double)cpuInfoStart.getNi()) / total;
  
  usage.sy = _MAXPERCENT * ((double)cpuInfoEnd.getSy() -
			    (double)cpuInfoStart.getSy()) / total;
  
  usage.id = _MAXPERCENT * idle / total;
  
  usage.wa = _MAXPERCENT * ((double)cpuInfoEnd.getWa() -
			    (double)cpuInfoStart.getWa()) / total;
  
  usage.irq = _MAXPERCENT * ((double)cpuInfoEnd.getIrq() -
			     (double)cpuInfoStart.getIrq()) / total;
  
  usage.sirq = _MAXPERCENT * ((double)cpuInfoEnd.getSirq() -
			      (double)cpuInfoStart.getSirq()) / total;
  
  usage.st = _MAXPERCENT * ((double)cpuInfoEnd.getSt() -
			    (double)cpuInfoStart.getSt()) / total;
  
  usage.gu = _MAXPERCENT * ((double)cpuInfoEnd.getGu() -
			    (double)cpuInfoStart.getGu()) / total;
  
  usage.gun = _MAXPERCENT * ((double)cpuInfoEnd.getGun() -
			     (double)cpuInfoStart.getGun()) / total;

  usage.utilization = _MAXPERCENT * (total - idle) / total;

  return usage;
} // end of "calcCPUUsage"
