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
   Calculates the current time spent on CPU for the values
   st, sy, ni id, wa, irq, sirq, st, gu, and gun.  This is done by
   doing basic math calculations based on start and end read related
   data values.

  Guarantee: Basic Guarantee

  Input:
   cpuInfoStart         - A const reference to CPUInfo object that
                          contains the start interval read for cpu
                          time values from the proc/stat file.

   cpuInfoStart         - A const reference to CPUInfo object that
                          contains the end interval read for cpu
                          time values from the proc/stat file.
   
  Output:
   CPUUsage             - A local CPUUsage object that is returned
                          by value containing the resulting cpu time
                          and utilization values.
   
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
  startIdle = (startIdle >= 0) ? startIdle : 0;
  
  endIdle = cpuInfoEnd.getId() + cpuInfoEnd.getWa();
  endIdle = (endIdle >= 0) ? endIdle : 0;  

  startNonIdle = cpuInfoStart.getUs() + cpuInfoStart.getNi() +
    cpuInfoStart.getSy() + cpuInfoStart.getIrq() + cpuInfoStart.getSirq() +
    cpuInfoStart.getSt();
  startNonIdle = (startNonIdle >= 0) ? startNonIdle : 0;

  endNonIdle = cpuInfoEnd.getUs() + cpuInfoEnd.getNi() + cpuInfoEnd.getSy() +
    cpuInfoEnd.getIrq() + cpuInfoEnd.getSirq() + cpuInfoEnd.getSt();
  endNonIdle = (endNonIdle >= 0) ? endNonIdle : 0;

  startTime = startIdle + startNonIdle;
  endTime = endIdle + endNonIdle;

  total = endTime - startTime;
  total = (total >= 0) ? total : 0;

  idle = endIdle - startIdle;
  idle = (idle >= 0) ? idle : 0;

  usage.us = _MAXPERCENT * (static_cast<double>(cpuInfoEnd.getUs()) - 
			    static_cast<double>(cpuInfoStart.getUs())) / total;
  usage.us = (usage.us >= 0) ? usage.us : 0;
  
  usage.ni = _MAXPERCENT * (static_cast<double>(cpuInfoEnd.getNi()) -
			    static_cast<double>(cpuInfoStart.getNi())) / total;
  usage.ni = (usage.ni >= 0) ? usage.ni : 0;
  
  usage.sy = _MAXPERCENT * (static_cast<double>(cpuInfoEnd.getSy()) -
			    static_cast<double>(cpuInfoStart.getSy())) / total;
  usage.sy = (usage.sy >= 0) ? usage.sy : 0;  
  
  usage.id = _MAXPERCENT * idle / total;
  usage.id = (usage.id >= 0) ? usage.id : 0;  
  
  usage.wa = _MAXPERCENT * (static_cast<double>(cpuInfoEnd.getWa()) -
			    static_cast<double>(cpuInfoStart.getWa())) / total;
  usage.wa = (usage.wa >= 0) ? usage.wa : 0;  
  
  usage.irq = _MAXPERCENT * (static_cast<double>(cpuInfoEnd.getIrq()) -
			     static_cast<double>(cpuInfoStart.getIrq())) / total;
  usage.irq = (usage.irq >= 0) ? usage.irq : 0;  
  
  usage.sirq = _MAXPERCENT * (static_cast<double>(cpuInfoEnd.getSirq()) -
			      static_cast<double>(cpuInfoStart.getSirq())) / total;
  usage.sirq = (usage.sirq >= 0) ? usage.sirq : 0;  
  
  usage.st = _MAXPERCENT * (static_cast<double>(cpuInfoEnd.getSt()) -
			    static_cast<double>(cpuInfoStart.getSt())) / total;
  usage.st = (usage.st >= 0) ? usage.st : 0;  
  
  usage.gu = _MAXPERCENT * (static_cast<double>(cpuInfoEnd.getGu()) -
			    static_cast<double>(cpuInfoStart.getGu())) / total;
  usage.gu = (usage.gu >= 0) ? usage.gu : 0;
  
  usage.gun = _MAXPERCENT * (static_cast<double>(cpuInfoEnd.getGun()) -
			     static_cast<double>(cpuInfoStart.getGun())) / total;
  usage.gun = (usage.gun >= 0) ? usage.gun : 0;

  usage.utilization = _MAXPERCENT - usage.id; 
  usage.utilization = (usage.utilization >= 0) ? usage.utilization : 0; 

  return usage;
} // end of "calcCPUUsage"
