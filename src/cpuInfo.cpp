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

  Input:

  Output:
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
   setUs

  Description:

  Input:

  Output:
 */
void CPUInfo::setUs(const unsigned int& us)
{
  m_us = us;
} // end of "setUs"



/*
  Function:
   setNi

  Description:

  Input:

  Output:
 */
void CPUInfo::setNi(const unsigned int& ni)
{
  m_ni = ni;
} // end of "setNi"



/*
  Function:
   setSy

  Description:

  Input:

  Output:
 */
void CPUInfo::setSy(const unsigned int& sy)
{
  m_sy = sy;
} // end of "setSy"



/*
  Function:
   setId

  Description:

  Input:

  Output:
 */
void CPUInfo::setId(const unsigned int& id)
{
  m_id = id;
} // end of "setId"



/*
  Function:
   setWa

  Description:

  Input:

  Output:
 */
void CPUInfo::setWa(const unsigned int& wa)
{
  m_wa = wa;
} // end of "setWa"



/*
  Function:
   setIrq

  Description:

  Input:

  Output:
 */
void CPUInfo::setIrq(const unsigned int& irq)
{
  m_irq = irq;
} // end of "setIrq"



/*
  Function:
   setSirq

  Description:

  Input:

  Output:
 */
void CPUInfo::setSirq(const unsigned int& sirq)
{
  m_sirq = sirq;
} // end of "setSirq"



/*
  Function:
   setSt

  Description:

  Input:

  Output:
 */
void CPUInfo::setSt(const unsigned int& st)
{
  m_st = st;
} // end of "setSt"



/*
  Function:
   setGu

  Description:

  Input:

  Output:
*/
void CPUInfo::setGu(const unsigned int& gu)
{
  m_gu = gu;
} // end of "setGu"



/*
  Function:
   setGun

  Description:

  Input:

  Output:
*/
void CPUInfo::setGun(const unsigned int& gun)
{
  m_gun = gun;
} // end of "setGun"



/*
  Function:
   getUs

  Description:

  Input:

  Output:
*/
const unsigned int& CPUInfo::getUs() const
{
  return m_us;
} // end of "getUs"



/*
  Function:
   getNi

  Description:

  Input:

  Output:
*/
const unsigned int& CPUInfo::getNi() const
{
  return m_ni;
} // end of "getNi"



/*
  Function:
   getSy

  Description:

  Input:

  Output:
*/
const unsigned int& CPUInfo::getSy() const
{
  return m_sy;
} // end of "getSy"



/*
  Function:
   getId

  Description:

  Input:

  Output:
*/
const unsigned int& CPUInfo::getId() const
{
  return m_id;
} // end of "getId"



/*
  Function:
   getWa

  Description:

  Input:

  Output:
*/
const unsigned int& CPUInfo::getWa() const
{
  return m_wa;
} // end of "getWa"



/*
  Function:
   getIrq

  Description:

  Input:

  Output:
*/
const unsigned int& CPUInfo::getIrq() const
{
  return m_irq;
} // end of "getIrq"



/*
  Function:
   getSirq

  Description:

  Input:

  Output:
*/
const unsigned int& CPUInfo::getSirq() const
{
  return m_sirq;
} // end of "getSirq"



/*
  Function:
   getSt

  Description:

  Input:

  Output:
*/
const unsigned int& CPUInfo::getSt() const
{
  return m_st;
} // end of "getSt"



/*
  Function:
   getGu

  Description:

  Input:

  Output:
*/
const unsigned int& CPUInfo::getGu() const
{
  return m_gu;
} // end of "getGu"



/*
  Function:
   getGun

  Description:

  Input:

  Output:
*/
const unsigned int& CPUInfo::getGun() const
{
  return m_gun;
} // end of "getGun"



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
