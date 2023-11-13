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
  double us;
  double ni;
  double sy;
  double id;
  double wa;
  double irq;
  double sirq;
  double st;
  double gu;
  double gun;
  double utilization;
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
  void setUs(const unsigned int& us) { m_us = us; }
  void setNi(const unsigned int& ni) { m_ni = ni; }
  void setSy(const unsigned int& sy) { m_sy = sy; }
  void setId(const unsigned int& id) { m_id = id; }
  void setWa(const unsigned int& wa) { m_wa = wa; }
  void setIrq(const unsigned int& irq) { m_irq = irq; }
  void setSirq(const unsigned int& sirq) { m_sirq = sirq; }
  void setSt(const unsigned int& st) { m_st = st; }
  void setGu(const unsigned int& gu) { m_gu = gu; }
  void setGun(const unsigned int& gun) { m_gun = gun; }
  
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
