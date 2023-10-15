/*
  File: cpuInfo.hpp
  
  Description:
  The CPUInfo class is used to store and calcualte CPU related values read from
  "/proc/" directory files.
 */
#ifndef CPUINFO_HPP
#define CPUINFO_HPP
#include "extractFileData.hpp"

class CPUInfo{
public:
  CPUInfo(const double& ticks = 0,
	  const double& jiffs = 0,
	  const double& us = 0,
	  const double& ni = 0,
	  const double& sy = 0,
	  const double& id = 0,
	  const double& wa = 0,
	  const double& irq = 0,
	  const double& sirq = 0,
	  const double& hi = 0,
	  const double& st = 0,
	  const double& gu = 0,
	  const double& gun = 0);

  // member functions
  const double calculateJiffs() { return m_us + m_ni + m_sy + m_id +
                                         m_wa + m_irq +m_sirq + m_st + m_gu + m_gun; }
  const double getAvgUs() { return (m_ticks * m_us)/m_jiffs; }
  const double getAvgHi() { return (100 * m_hi)/m_jiffs; }
  const double getAvgSy() { return (m_ticks * m_sy)/m_jiffs; }
  const double getAvgNi() { return (m_ticks * m_ni)/m_jiffs; }
  const double getAvgId() { return (m_ticks * m_id)/m_jiffs; }
  const double getAvgWa() { return (m_ticks * m_wa)/m_jiffs; }
  const double getAvgSt() { return (m_ticks * m_st)/m_jiffs; }
  //const double getAvgUs() { return (100 - getAvgId()); }
  
  // setters
  void setTicks(const double& ticks) { m_ticks = ticks; }
  void setJiffs(const double& jiffs) { m_jiffs = jiffs; }
  void setUs(const double& us) { m_us = us; }
  void setNi(const double& ni) { m_ni = ni; }
  void setSy(const double& sy) { m_sy = sy; }
  void setId(const double& id) { m_id = id; }
  void setWa(const double& wa) { m_wa = wa; }
  void setIrq(const double& irq) { m_irq = irq; }
  void setSirq(const double& sirq) { m_sirq = sirq; }
  void setSt(const double& st) { m_st = st; }  
  void setGu(const double& gu) { m_gu = gu; }
  void setGun(const double& gun) { m_gun = gun; }

  // getters
  const double& getTicks() { return m_ticks; }
  const double& getJiffs() { return m_jiffs; }  
  const double& getUs() { return m_us; }
  const double& getNi() { return m_ni; }
  const double& getSy() { return m_sy; }
  const double& getId() { return m_id; }
  const double& getWa() { return m_wa; }
  const double& getIrq() { return m_irq; }
  const double& getSirq() { return m_sirq; }
  const double& getSt() { return m_st; }
  const double& getGu() { return m_gu; }
  const double& getGun() { return m_gun; }

private:
  double m_ticks;
  double m_jiffs;
  double m_us;
  double m_ni;
  double m_sy;
  double m_id;
  double m_wa;
  double m_irq;
  double m_sirq;
  double m_hi;
  double m_st;
  double m_gu;
  double m_gun;
};

#endif
