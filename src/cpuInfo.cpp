/*
  File: cpuInfo.cpp
  
  Description:
   The CPUInfo class function implementations from the
   cpuInfo.hpp header file.
 */
#include "cpuInfo.hpp"



/*
  Function:
   CPUInfo Constructor

  Description:

  Input:

  Output:
 */
CPUInfo::CPUInfo(const double& ticks,
		 const double& jiffs,
		 const double& us,
		 const double& ni,
		 const double& sy,
		 const double& id,
		 const double& wa,
		 const double& irq,
		 const double& sirq,
		 const double& hi,
		 const double& st,
		 const double& gu,
		 const double& gun)
{
  setTicks(ticks);
  setJiffs(jiffs);
  setUs(us);
  setNi(ni);
  setSy(sy);
  setId(id);
  setWa(wa);
  setIrq(irq);
  setSirq(sirq);
  setHi(hi);
  setSt(st);
  setGu(gu);
  setGun(gun);
} // end of "CPUInfo constructor"



/*
  Function:
   calculateJiffs

  Description:

  Input:

  Output:
 */
const double& CPUInfo::calculateJiffs() const
{
  return
    getUs() +
    getNi() +
    getSy() +
    getId() +
    getWa() +
    getIrq() +
    getSirq() +
    getGu() +
    getGun();
} // end of "calculateJiffs"



/*
  Function:
   getAvgUs

  Description:

  Input:

  Output:
 */
const double& CPUInfo::getAvgUs() const
{
  return (getTicks() * getUs())/getJiffs();
} // end of "getAvgUs"



/*
  Function:
   getAvgHi

  Description:

  Input:

  Output:
 */
const double& CPUInfo::getAvgHi() const
{
  return (100 * getHi())/getJiffs();
} // end of "getAvgHi"



/*
  Function:
   getAvgSy

  Description:

  Input:

  Output:
 */
const double& CPUInfo::getAvgSy() const
{
  return (getTicks() * getSy())/getJiffs();  
} // end of "getAvgSy"



/*
  Function:
   getAvgNi

  Description:

  Input:

  Output:
 */
const double& CPUInfo::getAvgNi() const
{
  return (getTicks() * getNi())/getJiffs();
} // end of "getAvgNi"



/*
  Function:
   getAvgId

  Description:

  Input:

  Output:
 */
const double& CPUInfo::getAvgId() const
{
  return (getTicks() * getId())/getJiffs();
} // end of "getAvgId"



/*
  Function:
   getAvgWa

  Description:

  Input:

  Output:
 */
const double& CPUInfo::getAvgWa() const
{
  return (getTicks() * getWa())/getJiffs();
} // end of "getAvgWa"



/*
  Function:
   getAvgSt

  Description:

  Input:

  Output:
 */
const double& CPUInfo::getAvgSt() const
{
  return (getTicks() * getSt())/getJiffs();
} // end of "getAvgSt"



/*
  Function:
   setTicks

  Description:

  Input:

  Output:
 */
void CPUInfo::setTicks(const double& ticks)
{
  m_ticks = ticks;
} // end of "setTicks"



/*
  Function:
   setJiffs

  Description:

  Input:

  Output:
 */
void CPUInfo::setJiffs(const double& jiffs)
{
  m_jiffs = jiffs;
} // end of "setJiffs"



/*
  Function:
   setUs

  Description:

  Input:

  Output:
 */
void CPUInfo::setUs(const double& us)
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
void CPUInfo::setNi(const double& ni)
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
void CPUInfo::setSy(const double& sy)
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
void CPUInfo::setId(const double& id)
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
void CPUInfo::setWa(const double& wa)
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
void CPUInfo::setIrq(const double& irq)
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
void CPUInfo::setSirq(const double& sirq)
{
  m_sirq = sirq;
} // end of "setSirq"



/*
  Function:
   setHi

  Description:

  Input:

  Output:
 */
void CPUInfo::setHi(const double& hi)
{
  m_hi = hi;
} // end of "setHi"



/*
  Function:
   setSt

  Description:

  Input:

  Output:
 */
void CPUInfo::setSt(const double& st)
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
void CPUInfo::setGu(const double& gu)
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
void CPUInfo::setGun(const double& gun)
{
  m_gun = gun;
} // end of "setGun"



/*
  Function:
   getTicks

  Description:

  Input:

  Output:
*/
const double& CPUInfo::getTicks() const
{
  return m_ticks;
} // end of "getTicks"



/*
  Function:
   getJiffs

  Description:

  Input:

  Output:
*/
const double& CPUInfo::getJiffs() const
{
  return m_jiffs;
} // end of "getJiffs"



/*
  Function:
   getUs

  Description:

  Input:

  Output:
*/
const double& CPUInfo::getUs() const
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
const double& CPUInfo::getNi() const
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
const double& CPUInfo::getSy() const
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
const double& CPUInfo::getId() const
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
const double& CPUInfo::getWa() const
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
const double& CPUInfo::getIrq() const
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
const double& CPUInfo::getSirq() const
{
  return m_sirq;
} // end of "getSirq"



/*
  Function:
   getHi

  Description:

  Input:

  Output:
*/
const double& CPUInfo::getHi() const
{
  return m_hi;
} // end of "getHi"



/*
  Function:
   getSt

  Description:

  Input:

  Output:
*/
const double& CPUInfo::getSt() const
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
const double& CPUInfo::getGu() const
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
const double& CPUInfo::getGun() const
{
  return m_gun;
} // end of "getGun"
