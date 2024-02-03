/*
  File:
   cpuInfo.hpp
  
  Description:
   The CPUInfo class is used to store and calcualte CPU related values read from
   "/proc/stat" directory file.
 */
#ifndef CPUINFO_HPP
#define CPUINFO_HPP
#include <mutex>

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

  // setters
  void setUs(const unsigned int& us) {
    std::lock_guard<std::mutex> lock(m_usMut);
    m_us = us; }
  void setNi(const unsigned int& ni) {
    std::lock_guard<std::mutex> lock(m_niMut);
    m_ni = ni; }
  void setSy(const unsigned int& sy) {
    std::lock_guard<std::mutex> lock(m_syMut);
    m_sy = sy; }
  void setId(const unsigned int& id) {
    std::lock_guard<std::mutex> lock(m_idMut);
    m_id = id; }
  void setWa(const unsigned int& wa) {
    std::lock_guard<std::mutex> lock(m_waMut);
    m_wa = wa; }
  void setIrq(const unsigned int& irq) {
    std::lock_guard<std::mutex> lock(m_irqMut);
    m_irq = irq; }
  void setSirq(const unsigned int& sirq) {
    std::lock_guard<std::mutex> lock(m_sirqMut);
    m_sirq = sirq; }
  void setSt(const unsigned int& st) {
    std::lock_guard<std::mutex> lock(m_stMut);
    m_st = st; }
  void setGu(const unsigned int& gu) {
    std::lock_guard<std::mutex> lock(m_guMut);
    m_gu = gu; }
  void setGun(const unsigned int& gun) {
    std::lock_guard<std::mutex> lock(m_gunMut);
    m_gun = gun; }

  // overloaded operators
  CPUInfo& operator=(const CPUInfo& other);
  
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

  mutable std::mutex m_usMut;
  mutable std::mutex m_niMut;
  mutable std::mutex m_syMut;
  mutable std::mutex m_idMut;
  mutable std::mutex m_waMut;
  mutable std::mutex m_irqMut;
  mutable std::mutex m_sirqMut;
  mutable std::mutex m_stMut;
  mutable std::mutex m_guMut;
  mutable std::mutex m_gunMut;
};

CPUUsage calcCPUUsage(const CPUInfo& cpuInfoStart,
		      const CPUInfo& cpuInfoEnd);

#endif
