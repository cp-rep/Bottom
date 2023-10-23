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
			 const char& s,
			 const bool& changed)
{
  setPID(pid);
  setUSER(user);
  setPR(pr);
  setNI(ni);
  setVIRT(virt);
  setRES(res);
  setSHR(shr);
  setCPUUsage(cpuUsage);
  setMEMUsage(memUsage);
  setProcessCPUTime(processCPUTime);
  setCOMMAND(command);
  setS(0);
  setChanged(false);
} // end of "ProcessInfo Default Constructor"



/*
  Function:
   getPID
   
  Description:

  Input:

  Output:
*/
const int& ProcessInfo::getPID() const
{
  return m_pid;
} // end of "getPID"



/*
  Function:
   getUSER
   
  Description:

  Input:

  Output:
*/
const std::string& ProcessInfo::getUSER() const
{
  return m_user;
} // end of "getUSER"



/*
  Function:
   getPR
   
  Description:

  Input:

  Output:
*/
const int& ProcessInfo::getPR() const
{
  return m_pr;
} // end of "getPR"



/*
  Function:
   getNI
  Description:

  Input:

  Output:
*/
const short& ProcessInfo::getNI() const
{
  return m_ni;
} // end of "getNI"



/*
  Function:
   getVIRT
   
  Description:

  Input:

  Output:
*/
const unsigned int& ProcessInfo::getVIRT() const
{
  return m_virt;
} // end of "getVIRT"



/*
  Function:
   getRES
   
  Description:

  Input:

  Output:
*/
const unsigned int& ProcessInfo::getRES() const
{
  return m_res;
} // end of "getRES"



/*
  Function:
   getSHR
   
  Description:

  Input:

  Output:
*/
const unsigned int& ProcessInfo::getSHR() const
{
  return m_shr;
} // end of "getSHR"



/*
  Function:
   getS
   
  Description:

  Input:

  Output:
*/
const char& ProcessInfo::getS() const
{
  return m_s;
} // end of "getS"



/*
  Function:
   getCPUUsage
   
  Description:

  Input:

  Output:
*/
const double& ProcessInfo::getCPUUsage() const
{
  return m_cpuUsage;
} // end of "getCPUUsage"



/*
  Function:
   getMEMUsage
  
  Description:

  Input:

  Output:
*/
const double& ProcessInfo::getMEMUsage() const
{
  return m_memUsage;
} // end of "getMEMUsage"



/*
  Function:
   getCpuRawTime
   
  Description:

  Input:

  Output:
*/
const double& ProcessInfo::getCpuRawTime() const
{
  return m_cpuRawTime;
} // end of "getCpuRawTime"



/*
  Function:
   getProcessCPUTime
   
  Description:

  Input:

  Output:
*/
const std::string& ProcessInfo::getProcessCPUTime() const
{
  return m_processCPUTime;
} // end of "getProcessCPUTime"



/*
  Function:
   getCOMMAND
   
  Description:

  Input:

  Output:
*/
const std::string& ProcessInfo::getCOMMAND() const
{
  return m_command;
} // end of "getCOMMAND"



/*
  Function:
   getChanged
   
  Description:

  Input:

  Output:
*/
const bool& ProcessInfo::getChanged() const
{
  return m_changed;
} // end of "getChanged"



/*
  Function:
   setPID
   
  Description:

  Input:

  Output:
*/
void ProcessInfo::setPID(const int& pid)
{
  m_pid = pid;
} // end of "setPID"



/*
  Function:
   setUSER
   
  Description:

  Input:

  Output:
*/
void ProcessInfo::setUSER(const std::string& user)
{
  m_user = user;
} // end of "setUSER"



/*
  Function:
   setPR
   
  Description:

  Input:

  Output:
*/
void ProcessInfo::setPR(const int& pr)
{
  m_pr = pr;
} // end of "setPR"



/*
  Function:
   setNI
   
  Description:

  Input:

  Output:
*/
void ProcessInfo::setNI(const short& ni)
{
  m_ni = ni;
} // end of "setNI"



/*
  Function:
   setVIRT
   
  Description:

  Input:

  Output:
*/
void ProcessInfo::setVIRT(const unsigned int& virt)
{
  m_virt = virt;
} // end of "setVIRT"



/*
  Function:
   setRES
   
  Description:

  Input:

  Output:
*/
void ProcessInfo::setRES(const unsigned int& res)
{
  m_res = res;
} // end of "setRES"



/*
  Function:
   setSHR
   
  Description:

  Input:

  Output:
*/
void ProcessInfo::setSHR(const unsigned int& shr)
{
  m_shr = shr;
} // end of "setSHR"



/*
  Function:
   setS
   
  Description:

  Input:

  Output:
*/
void ProcessInfo::setS(const char& s)
{
  m_s = s;
} // end of "setS"



/*
  Function:
   setCPUUsage
   
  Description:

  Input:

  Output:
*/
void ProcessInfo::setCPUUsage(const double& cpuUsage)
{
  m_cpuUsage = cpuUsage;
} // end of "setCPUUsage"



/*
  Function:
   setMEMUsage
   
  Description:

  Input:

  Output:
*/
void ProcessInfo::setMEMUsage(const double& memUsage)
{
  m_memUsage = memUsage;
} // end of "setMEMUsage"



/*
  Function:
   setCpuRawTime
   
  Description:

  Input:

  Output:
*/
void ProcessInfo::setCpuRawTime(const double& cpuRawTime)
{
  m_cpuRawTime = cpuRawTime;
} // end of "setCpuRawTime"



/*
  Function:
   setProcessCPUTime
  
  Description:

  Input:

  Output:
*/
void ProcessInfo::setProcessCPUTime(const std::string& processCPUTime)
{
  m_processCPUTime = processCPUTime;
} // end of "setProcessCPUTime"



/*
  Function:
   setCOMMAND
   
  Description:

  Input:

  Output:
*/
void ProcessInfo::setCOMMAND(const std::string& command)
{
  m_command = command;
} // end of "setCOMMAND"



/*
  Function:
   setChanged
   
  Description:

  Input:

  Output:
*/
void ProcessInfo::setChanged(const bool& changed)
{
  m_changed = changed;
} // end of "setChanged"
