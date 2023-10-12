/*
  File: processInfo.hpp
  
  Description:
  The ProcessInfo class is used to store information about processes found
  from the "/proc/" folder and its subdirectories.
 */
#ifndef PROCESSWINDOW_HPP
#define PROCESSWINDOW_HPP
#include <string>

class ProcessInfo{
public:
  ProcessInfo(const int& pid = 0,
	      const std::string& user = "",
	      const unsigned short& pr = 0,
	      const unsigned short& ni = 0,
	      const unsigned int& virt = 0,
	      const unsigned int& res = 0,
	      const unsigned int& shr = 0,
	      const double& cpuUsage = 0,
	      const double& memUsage = 0,
	      const std::string& command = "",
	      const std::string& processCPUTime = "N/A",
	      const char s = ' ',
	      const bool changed = false);

  // getters
  const int& getPID() { return m_pid; }
  const std::string& getUSER() { return m_user; }
  const std::string& getPR() { return m_pr; }
  const short& getNI() { return m_ni; }
  const unsigned int& getVIRT() { return m_virt; }
  const unsigned int& getRES() { return m_res; }
  const unsigned int& getSHR() { return m_shr; }
  const char& getS() { return m_s; }
  const double& getCPUUsage() { return m_cpuUsage; }
  const double& getMEMUsage() { return m_memUsage; }
  const std::string& getProcessCPUTime() { return m_processCPUTime; }
  const std::string& getCOMMAND() { return m_command; }
  
  // setters
  void setPID(const int& pid) { m_pid = pid; }
  void setUSER(const std::string& user) { m_user = user; }
  void setPR(const std::string& pr) { m_pr = pr; }
  void setNI(const short& ni) { m_ni = ni; }
  void setVIRT(const unsigned int& virt) { m_virt = virt; }
  void setRes(const unsigned int& res) { m_res = res; }
  void setSHR(const unsigned int& shr) { m_shr = shr; }
  void setS(const char& s) { m_s = s; }
  void setCPUUsage(const double& cpuUsage) { m_cpuUsage = cpuUsage; }
  void setMEMUsage(const double& memUsage) { m_memUsage = memUsage; }
  void setProcessCPUTime(const std::string processCPUTime)
  { m_processCPUTime = processCPUTime; }
  void setCOMMAND(const std::string& command) { m_command = command; }
  
private:
  int m_pid;
  std::string m_user;
  std::string m_pr;
  short m_ni;
  unsigned int m_virt;
  unsigned int m_res;
  unsigned int m_shr;
  char m_s;
  double m_cpuUsage;
  double m_memUsage;
  std::string m_processCPUTime;
  std::string m_command;
  bool m_changed;
};

#endif
