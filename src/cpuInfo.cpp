/*
  File: cpuInfo.cpp
  
  Description:
  The CPUInfo class function implementations from the
  cpuInfo.hpp header file.
 */
#include "cpuInfo.hpp"



/*
  Function:
   CPUInfo Default Constructor

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
  m_ticks = ticks;
  m_jiffs = jiffs;
  m_us = us;
  m_ni = ni;
  m_sy = sy;
  m_id = id;
  m_wa = wa;
  m_irq = irq;
  m_sirq = sirq;
  m_hi = hi;
  m_st = st;
  m_gu = gu;
  m_gun = gun;
 } // end of "default constructor"



