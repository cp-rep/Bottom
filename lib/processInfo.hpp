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
  
private:
  std::string m_pid;
  std::string m_user;
  unsigned int ni;
  std::string m_ni;

  std::string m_command;
  std::string m_cpuPercent;
  
};


#endif
