/*
  File:
   processInfo.hpp
  
  Description:
   The ProcessInfo class is used to store information about processes found
   from the "/proc/" folder and its subdirectories.
 */
#ifndef PROCESSINFO_HPP
#define PROCESSINFO_HPP
#include <string>
#include <iostream>
#include <mutex>

class ProcessInfo{
public:
  ProcessInfo(const unsigned int& pid = 0,
	      const std::string& user = "",
	      const unsigned int& pr = 0,
	      const unsigned int& ni = 0,
	      const unsigned int& virt = 0,
	      const unsigned int& res = 0,
	      const unsigned int& shr = 0,
	      const double& cpuUsage = 0,
	      const double& memUsage = 0,
	      const std::string& command = "",
	      const std::string& processCPUTime = "",
	      const char& s = ' ',
	      const bool& changed = false,
	      const double& utime = 0,
	      const double& stime = 0,	      
	      const double& cutime = 0,
	      const double& cstime = 0,	      
	      const double& pstart = 0);

  ProcessInfo(const ProcessInfo& other);

  // operators
  bool operator==(const ProcessInfo& other) const;
  ProcessInfo& operator=(const ProcessInfo& other);

  // getters
  const unsigned int& getPID() const { return m_pid; }
  const std::string& getUSER() const { return m_user; }
  const int& getPR() const { return m_pr; }
  const int& getNI() const { return m_ni; }
  const unsigned int& getVIRT() const { return m_virt; }
  const unsigned int& getRES() const { return m_res; }
  const unsigned int& getSHR() const { return m_shr; }
  const char& getS() const { return m_s; }
  const double& getCPUUsage() const { return m_cpuUsage; }
  const double& getMEMUsage() const { return m_memUsage; }
  const double& getCpuRawTime() const { return m_cpuRawTime; }
  const std::string& getProcessCPUTime() const { return m_processCPUTime; }
  const std::string& getCOMMAND() const { return m_command; }
  const std::string& getCOMMANDUpper() const { return m_commandUpper; }
  const bool& getChanged() const { return m_changed; }
  const double& getUTime() const { return m_utime; }
  const double& getSTime() const { return m_stime; }
  const double& getCUTime() const { return m_cutime; }
  const double& getCSTime() const { return m_cstime; }
  const double& getPStart() const { return m_pstart; }
  
  // setters
  void setPID(const unsigned int& pid) {
    std::lock_guard<std::mutex> lock(m_pidMut);
    m_pid = pid; }
  void setUSER(const std::string& user) {
    std::lock_guard<std::mutex> lock(m_userMut);
    m_user = user; }
  void setPR(const int& pr) {
    std::lock_guard<std::mutex> lock(m_prMut);
    m_pr = pr; }
  void setNI(const int& ni) {
    std::lock_guard<std::mutex> lock(m_niMut);
    m_ni = ni; }
  void setVIRT(const unsigned int& virt) {
    std::lock_guard<std::mutex> lock(m_virtMut);
    m_virt = virt; }
  void setRES(const unsigned int& res) {
    std::lock_guard<std::mutex> lock(m_resMut);
    m_res = res; }
  void setSHR(const unsigned int& shr) {
    std::lock_guard<std::mutex> lock(m_shrMut);
    m_shr = shr; }
  void setS(const char& s) {
    std::lock_guard<std::mutex> lock(m_sMut);
    m_s = s; }
  void setCPUUsage(const double& cpuUsage) {
    std::lock_guard<std::mutex> lock(m_cpuUsageMut);
    m_cpuUsage = cpuUsage; }
  void setMEMUsage(const double& memUsage) {
    std::lock_guard<std::mutex> lock(m_memUsageMut);
    m_memUsage = memUsage; }
  void setCpuRawTime(const double& cpuRawTime) {
    std::lock_guard<std::mutex> lock(m_cpuRawTimeMut);
    m_cpuRawTime = cpuRawTime; }
  void setProcessCPUTime(const std::string& processCPUTime) {
    std::lock_guard<std::mutex> lock(m_processCPUTimeMut);
    m_processCPUTime = processCPUTime; }
  void setCOMMAND(const std::string& command);
  void setCOMMANDUpper(const std::string& command);
  void setChanged(const bool& changed) {
    std::lock_guard<std::mutex> lock(m_changedMut);
    m_changed = changed; }
  void setUTime(const double& utime) {
    std::lock_guard<std::mutex> lock(m_utimeMut);
    m_utime = utime; }
  void setSTime(const double& stime) {
    std::lock_guard<std::mutex> lock(m_stimeMut);
    m_stime = stime; }
  void setCUTime(const double& cutime) {
    std::lock_guard<std::mutex> lock(m_cutimeMut);
    m_cutime = cutime; }
  void setCSTime(const double& cstime) {
    std::lock_guard<std::mutex> lock(m_cstimeMut);
    m_cstime = cstime; }
  void setPStart(const double& pstart) {
    std::lock_guard<std::mutex> lock(m_pstartMut);
    m_pstart = pstart; }

  // member functions
  void calcProcCPUUsage(ProcessInfo& pInfoStart,
			ProcessInfo& pInfoEnd);
      
private:
  unsigned int m_pid;
  std::string m_user;
  int m_pr;
  int m_ni;
  unsigned int m_virt;
  unsigned int m_res;
  unsigned int m_shr;
  char m_s;
  double m_cpuUsage;
  double m_memUsage;
  double m_cpuRawTime;
  std::string m_processCPUTime;
  std::string m_command;
  std::string m_commandUpper;  
  bool m_changed;
  double m_utime;
  double m_stime;
  double m_cutime;
  double m_cstime;  
  double m_pstart;

  mutable std::mutex m_pidMut;
  mutable std::mutex m_userMut;
  mutable std::mutex m_prMut;
  mutable std::mutex m_niMut;
  mutable std::mutex m_virtMut;
  mutable std::mutex m_resMut;
  mutable std::mutex m_shrMut;
  mutable std::mutex m_sMut;
  mutable std::mutex m_cpuUsageMut;
  mutable std::mutex m_memUsageMut;
  mutable std::mutex m_cpuRawTimeMut;
  mutable std::mutex m_processCPUTimeMut;
  mutable std::mutex m_commandMut;
  mutable std::mutex m_commandUpperMut;
  mutable std::mutex m_changedMut;
  mutable std::mutex m_utimeMut;
  mutable std::mutex m_stimeMut;
  mutable std::mutex m_cutimeMut;
  mutable std::mutex m_cstimeMut;
  mutable std::mutex m_pstartMut;
};

std::ostream& operator<<(std::ostream& os, const ProcessInfo& processInfo);

#endif
