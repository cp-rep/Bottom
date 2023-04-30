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
	      const unsigned short& m_pr = 0,
	      const unsigned short& m_ni = 0,
	      const unsigned int& m_virt = 0,
	      const unsigned int& m_res = 0,
	      const unsigned int& m_shr = 0,
	      const char* s = nullptr,
	      const float& cpuUsage = 0,
	      const float& memUsage = 0,
	      const std::string& command = "");

  // getters
  const int& getPID() { return m_pid; }
  const std::string& getUser() { return m_user; }
  const unsigned short& getPR() { return m_pr; }
  const short& getNI() { return m_ni; }
  const unsigned int& getVirt() { return m_virt; }
  const unsigned int& getRes() { return m_res; }
  const unsigned int& getSHR() { return m_shr; }
  const char& getS() { return m_s; }
  const float& getCpuUsage() { return m_cpuUsage; }
  const float& getMemUsage() { return m_memUsage; }
  const std::string& getCommand() { return m_command; }
  
  // setters
  void setPID(const int& pid) { m_pid = pid; }
  void setUser(const std::string& user) { m_user = user; }
  void setPR(const unsigned short& pr) { m_pr = pr; }
  void setNI(const short& ni) { m_ni = ni; }
  void setVirt(const unsigned int& virt) { m_virt = virt; }
  void setRes(const unsigned int& res) { m_res = res; }
  void setSHR(const unsigned int& shr) { m_shr = shr; }
  void setS(const char& s) { m_s = s; }
  void setCpuUsage(const float& cpuUsage) { m_cpuUsage = cpuUsage; }
  void setMemUsage(const float& memUsage) { m_memUsage = memUsage; }
  void setCommand(const std::string& command) { m_command = command; }
  
private:
  int m_pid;
  std::string m_user;
  unsigned short m_pr;
  short m_ni;
  unsigned int m_virt;
  unsigned int m_res;
  unsigned int m_shr;
  char m_s;
  float m_cpuUsage;
  float m_memUsage;
  std::string m_command;
};

#endif
