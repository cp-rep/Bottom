/*
  File: processInfo.hpp
  
  Description:
  The ProcessInfo class is used to store information about processes found
  from the "/proc/" folder and its subdirectories.
 */
#ifndef PROCESSWINDOW_HPP
#define PROCESSWINDOW_HPP
#include <string>
#include <ctime>

class ProcessInfo{
public:
  
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
  struct tm m_processUptime;
  std::string m_command;
};


#endif
