/*
  File: processInfo.cpp
  Description:
  The ProcessInfo class implementation function definitions.
 */
#include "processInfo.hpp"

ProcessInfo::ProcessInfo(const unsigned int& pid,
			 const std::string& user,
			 const unsigned int& pr,
			 const unsigned int& ni,
			 const unsigned int& virt,
			 const unsigned int& res,
			 const unsigned int& shr,
			 const double& cpuUsage,
			 const double& memUsage,
			 const std::string& command,
			 const std::string& processCPUTime,
			 const char& s,
			 const bool& changed,
			 const double& utime,
			 const double& stime,			 
			 const double& cutime,
			 const double& cstime,			 			 
			 const double& pstart)
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
  setCOMMAND(command);  
  setProcessCPUTime(processCPUTime);
  setS(s);
  setChanged(changed);
  setUTime(utime);
  setSTime(stime);
  setCUTime(cutime);
  setCSTime(cstime);
  setPStart(pstart);
  setCpuRawTime(0);
} // end of "ProcessInfo Default Constructor"



/*
  Function:
   Copy Constructor

  Description:
   Initializes a new ProcessInfo object with the incoming parameter.

  Input:
   other                - A reference to a constant ProcessInfo object
                          used to initialize *this.

  Output:
   NONE
*/
ProcessInfo::ProcessInfo(const ProcessInfo& other)
{
  *this = other;
} // end of "Copy Constructor"





/*
  Function:
   Overloaded ==

  Description:
   Compares each member variable of the incoming ProcessInfo object to
   those of *this.  Returns true if they are equal, false otherwise.

  Input:
   other                - A reference to a constant ProcessInfo object
                          used to compare to *this.
   

  Output:
   bool                 - The result of the comparison.  True if all
                          member variables are equal, false otherwise.
*/
bool ProcessInfo::operator==(const ProcessInfo& other) const
{
  if(this->m_pid != other.getPID())
    {
      return false;
    }
  else if(this->m_user != other.getUSER())
    {
      return false;
    }
  else if(this->m_pr != other.getPR())
    {
      return false;
    }
  else if(this->m_ni != other.getNI())
    {
      return false;
    }
  else if(this->m_virt != other.getVIRT())
    {
      return false;
    }
  else if(this->m_res != other.getRES())
    {
      return false;
    }
  else if(this->m_shr != other.getSHR())
    {
      return false;
    }
  else if(this->m_s != other.getS())
    {
      return false;
    }
  else if(this->m_cpuUsage != other.getCPUUsage())
    {
      return false;
    }
  else if(this->m_memUsage != other.getMEMUsage())
    {
      return false;
    }
  else if(this->m_cpuRawTime != other.getCpuRawTime())
    {
      return false;
    }
  else if(this->m_processCPUTime != other.getProcessCPUTime())
    {
      return false;
    }
  else if(this->m_command != other.getCOMMAND())
    {
      return false;
    }
  else if(this->m_commandUpper != other.getCOMMANDUpper())
    {
      return false;
    }
  else if(this->m_changed != other.getChanged())
    {
      return false;
    }
  else if(this->m_utime != other.getUTime())
    {
      return false;
    }
  else if(this->m_stime != other.getSTime())
    {
      return false;
    }
  else if(this->m_cutime != other.getCUTime())
    {
      return false;
    }
  else if(this->m_cstime != other.getCSTime())
    {
      return false;
    }
  else if(this->m_pstart != other.getPStart())
    {
      return false;
    }

  return true;
} // end of "Overloaded =="



/*
  Function:
   Overloaded =

  Description:
   Copies all of the ProcessInfo object parameters member variables
   to those of *this.

  Input:
   other                - A reference to a constant ProcessInfo object
                          used to copy its member variables to *this.  
  Output:
   ProcessInfo          - The reference to *this for concatenation.
*/
ProcessInfo& ProcessInfo::operator=(const ProcessInfo& other)
{
  if(this != &other)
    {
      this->m_pid = other.getPID();
      this->m_user = other.getUSER();
      this->m_pr = other.getPR();
      this->m_ni = other.getNI();
      this->m_virt = other.getVIRT();
      this->m_res = other.getRES();
      this->m_shr = other.getSHR();
      this->m_s = other.getS();
      this->m_cpuUsage = other.getCPUUsage();
      this->m_memUsage = other.getMEMUsage();
      this->m_cpuRawTime = other.getCpuRawTime();
      this->m_processCPUTime = other.getProcessCPUTime();
      this->m_command = other.getCOMMAND();
      this->m_commandUpper = other.getCOMMANDUpper();
      this->m_changed = other.getChanged();
      this->m_utime = other.getUTime();
      this->m_stime = other.getSTime();
      this->m_cutime = other.getCUTime();
      this->m_cstime = other.getCSTime();
      this->m_pstart = other.getPStart();
    }

  return *this;
} // end of "Overloaded ="



/*
  Function:
   Overloaded <<

  Description:
   Allows the output stream to use ProcessInfo objects as arguments.

  Input:
   os                   - A reference to an ostream object being used
                          to call its output stream with ProcessInfo
			  objects.
  
   processInfo          - A reference to a const ProcessInfo object that
                          is being used to print its data to stdout.

  Output:
   ostream              - A reference to the output stream parameter for
                          concatenation.
*/
std::ostream& operator<<(std::ostream& os, const ProcessInfo& processInfo)
{
  os << "PID: " << processInfo.getPID() << std::endl;
  os << "USER: " << processInfo.getUSER() << std::endl;
  os << "PR: " << processInfo.getPR() << std::endl;
  os << "NI: " << processInfo.getNI() << std::endl;
  os << "VIRT: " << processInfo.getVIRT() << std::endl;
  os << "RES: " << processInfo.getRES() << std::endl;
  os << "SHR: " << processInfo.getSHR() << std::endl;
  os << "S: " << processInfo.getS() << std::endl;
  os << "CPU Usage: " << processInfo.getCPUUsage() << std::endl;
  os << "Mem Usage: " << processInfo.getMEMUsage() << std::endl;
  os << "CPU Raw Time: " << processInfo.getCpuRawTime() << std::endl;
  os << "Process CPU Time: " << processInfo.getProcessCPUTime() << std::endl;
  os << "COMMAND: " << processInfo.getCOMMAND() << std::endl;
  os << "COMMAND Upper: " << processInfo.getCOMMANDUpper() << std::endl;
  os << "utime: " << processInfo.getUTime() << std::endl;
  os << "stime: " << processInfo.getSTime() << std::endl;
  os << "cutime: " << processInfo.getCUTime()<< std::endl;
  os << "cstime: " << processInfo.getCSTime() << std::endl;
  os << "pstart: " << processInfo.getPStart() << std::endl;

  return os;
} // end of "Overloaded <<"



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
  setCOMMANDUpper(command);
} // end of "setCOMMAND"


/*
  Function:
   setCOMMANDUpper
   
  Description:

  Input:

  Output:
*/
void ProcessInfo::setCOMMANDUpper(const std::string& command)
{
  m_commandUpper.clear();
  for(int i = 0; i < command.length(); i++)
    {
      if((command.at(i) >= 'a' && command.at(i) <= 'z') ||
	 (command.at(i) >= 'A' && command.at(i) <= 'Z'))
	
	{
	  m_commandUpper.push_back(toupper(command.at(i)));
	}
    }
} // end of "getCOMMANDUpper"



/*
  Function:
   calcProcCPUUsage
   
  Description:

  Input:

  Output:

*/
double ProcessInfo::calcProcCPUUsage(ProcessInfo& pInfoStart,
				     ProcessInfo& pInfoEnd)
{
  double procCPUTime;
  
  procCPUTime = (pInfoEnd.getUTime() + pInfoEnd.getSTime() +
		 pInfoEnd.getCUTime() + pInfoEnd.getCSTime()) -
    (pInfoStart.getUTime() + pInfoStart.getSTime() +
     pInfoStart.getCUTime() + pInfoStart.getPStart());
    
  return procCPUTime;
} // end of "calcProcCPUUsage"
