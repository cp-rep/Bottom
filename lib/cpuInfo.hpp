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
  
private:
  double m_totalJiffs;
  double us;
  double ni;
  double sy;
  double id;
  double wa;
  double irq;
  double sirq;
  double hi;
  double si;
  double st;
  double gu;
  double gun;
};

#endif
