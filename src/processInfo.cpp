/*
  File: processInfo.cpp
  Description:
  The ProcessInfo class implementation function definitions.
 */
#include "processInfo.hpp"



ProcessInfo::ProcessInfo(const int& pid,
			 const std::string& user,
			 const unsigned short& pr,
			 const unsigned short& ni,
			 const unsigned int& virt,
			 const unsigned int& res,
			 const unsigned int& shr,
			 const double& cpuUsage,
			 const double& memUsage,
			 const std::string& command,
			 const std::string& processCPUTime,
			 const char s,
			 const bool changed)
{
  m_pid = pid;
  m_user = user;
  m_pr = pr;
  m_ni = ni;
  m_virt = virt;
  m_res = res;
  m_shr = shr;
  m_cpuUsage = cpuUsage;
  m_memUsage = memUsage;
  m_command = command;
  m_processCPUTime = processCPUTime;
  m_s = 0;
  m_changed = false;
} // end of "ProcessInfo Default Constructor"
