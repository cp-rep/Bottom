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
  ProcessInfo(const unsigned int& pid = 0,
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
  
private:
  unsigned int m_pid;
  std::string m_user;
  unsigned short m_pr;
  unsigned short m_ni;
  unsigned int m_virt;
  unsigned int m_res;
  unsigned int m_shr;
  char m_s;
  float m_cpuUsage;
  float m_memUsage;
  std::string m_command;
};


#endif
