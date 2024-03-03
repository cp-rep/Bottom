/*
  File:
   cpuInfo.hpp
  
  Description:
   The CPUInfo class is used to store and calcualte CPU related values read from
   "/proc/stat" directory file.
 */
#ifndef CPUINFO_HPP
#define CPUINFO_HPP

struct CPUUsage{
  double us = 0;
  double ni = 0;
  double sy = 0;
  double id = 0;
  double wa = 0;
  double irq = 0;
  double sirq = 0;
  double st = 0;
  double gu = 0;
  double gun = 0;
  double utilization = 0;
};

class CPUInfo{
public:
  CPUInfo(const unsigned int& us = 0,
	  const unsigned int& ni = 0,
	  const unsigned int& sy = 0,
	  const unsigned int& id = 0,
	  const unsigned int& wa = 0,
	  const unsigned int& irq = 0,
	  const unsigned int& sirq = 0,
	  const unsigned int& st = 0,
	  const unsigned int& gu = 0,
	  const unsigned int& gun = 0);

  // setters
  void setUs(const unsigned int& us) { m_us = (us >= 0) ? us : 0; }
  void setNi(const unsigned int& ni) { m_ni = (ni >= 0) ? ni : 0; }
  void setSy(const unsigned int& sy) { m_sy = (sy >= 0) ? sy : 0; }
  void setId(const unsigned int& id) { m_id = (id >= 0) ? id : 0; }
  void setWa(const unsigned int& wa) { m_wa = (wa >= 0) ? wa : 0; }
  void setIrq(const unsigned int& irq) { m_irq = (irq >= 0) ? irq : 0; }
  void setSirq(const unsigned int& sirq) { m_sirq = (sirq >= 0) ? sirq : 0; }
  void setSt(const unsigned int& st) { m_st = (st >= 0) ? st : 0; }
  void setGu(const unsigned int& gu) { m_gu = (gu >= 0) ? gu : 0; }
  void setGun(const unsigned int& gun) { m_gun = (gun >= 0) ? gun : 0; }
  
  // getters
  const unsigned int& getUs() const { return m_us; }
  const unsigned int& getNi() const { return m_ni; }
  const unsigned int& getSy() const { return m_sy; }
  const unsigned int& getId() const { return m_id; }
  const unsigned int& getWa() const { return m_wa; }
  const unsigned int& getIrq() const { return m_irq; }
  const unsigned int& getSirq() const { return m_sirq; }
  const unsigned int& getSt() const { return m_st; }
  const unsigned int& getGu() const { return m_gu; }
  const unsigned int& getGun() const { return m_gun; }

private:
  unsigned int m_us;
  unsigned int m_ni;
  unsigned int m_sy;
  unsigned int m_id;
  unsigned int m_wa;
  unsigned int m_irq;
  unsigned int m_sirq;
  unsigned int m_st;
  unsigned int m_gu;
  unsigned int m_gun;
};

CPUUsage calcCPUUsage(const CPUInfo& cpuInfoStart,
		      const CPUInfo& cpuInfoEnd);

#endif
