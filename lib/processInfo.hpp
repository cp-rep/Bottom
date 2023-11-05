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
	      const std::string& processCPUTime = "N/A",
	      const char& s = ' ',
	      const bool& changed = false);

  // getters
  const unsigned int& getPID() const;
  const std::string& getUSER() const;
  const unsigned int& getPR() const;
  const unsigned int& getNI() const;
  const unsigned int& getVIRT() const;
  const unsigned int& getRES() const;
  const unsigned int& getSHR() const;
  const char& getS() const;
  const double& getCPUUsage() const;
  const double& getMEMUsage() const;
  const double& getCpuRawTime() const;
  const std::string& getProcessCPUTime() const;
  const std::string& getCOMMAND() const;
  const bool& getChanged() const;
  
  // setters
  void setPID(const unsigned int& pid);
  void setUSER(const std::string& user);
  void setPR(const unsigned int& pr);
  void setNI(const unsigned int& ni);
  void setVIRT(const unsigned int& virt);
  void setRES(const unsigned int& res);
  void setSHR(const unsigned int& shr);
  void setS(const char& s);
  void setCPUUsage(const double& cpuUsage);
  void setMEMUsage(const double& memUsage);
  void setCpuRawTime(const double& cpuRawTime);
  void setProcessCPUTime(const std::string& processCPUTime);
  void setCOMMAND(const std::string& command);
  void setChanged(const bool& changed);
  
private:
  unsigned int m_pid;
  std::string m_user;
  unsigned int m_pr;
  unsigned int m_ni;
  unsigned int m_virt;
  unsigned int m_res;
  unsigned int m_shr;
  char m_s;
  double m_cpuUsage;
  double m_memUsage;
  double m_cpuRawTime;
  std::string m_processCPUTime;
  std::string m_command;
  bool m_changed;
};

#endif
