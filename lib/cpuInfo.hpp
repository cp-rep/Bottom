/*
  File: cpuInfo.hpp
  
  Description:
  The CPUInfo class is used to store and calcualte CPU related values read from
  "/proc/" directory files.
 */
#ifndef CPUINFO_HPP
#define CPUINFO_HPP

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
  const double& calculateJiffs() const;
  const double& getAvgUs() const;
  const double& getAvgHi() const;
  const double& getAvgSy() const;
  const double& getAvgNi() const;
  const double& getAvgId() const;
  const double& getAvgWa() const;
  const double& getAvgSt() const;
  //const double getAvgUs() { return (100 - getAvgId()); }
  
  // setters
  void setTicks(const double& ticks);
  void setJiffs(const double& jiffs);
  void setUs(const double& us);
  void setNi(const double& ni);
  void setSy(const double& sy);
  void setId(const double& id);
  void setWa(const double& wa);
  void setIrq(const double& irq);
  void setSirq(const double& sirq);
  void setHi(const double& hi);  
  void setSt(const double& st);
  void setGu(const double& gu);
  void setGun(const double& gun);
  
  // getters
  const double& getTicks() const;
  const double& getJiffs() const;
  const double& getUs() const;
  const double& getNi() const;
  const double& getSy() const;
  const double& getId() const;
  const double& getWa() const;
  const double& getIrq() const;
  const double& getSirq() const;
  const double& getHi() const;
  const double& getSt() const;
  const double& getGu() const;
  const double& getGun() const;

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
