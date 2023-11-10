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
  double hi;
  double si;
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
  void setUs(const unsigned int& us);
  void setNi(const unsigned int& ni);
  void setSy(const unsigned int& sy);
  void setId(const unsigned int& id);
  void setWa(const unsigned int& wa);
  void setIrq(const unsigned int& irq);
  void setSirq(const unsigned int& sirq);
  void setSt(const unsigned int& st);
  void setGu(const unsigned int& gu);
  void setGun(const unsigned int& gun);
  
  // getters
  const unsigned int& getUs() const;
  const unsigned int& getNi() const;
  const unsigned int& getSy() const;
  const unsigned int& getId() const;
  const unsigned int& getWa() const;
  const unsigned int& getIrq() const;
  const unsigned int& getSirq() const;
  const unsigned int& getHi() const;
  const unsigned int& getSt() const;
  const unsigned int& getGu() const;
  const unsigned int& getGun() const;

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
