/*
  File: sortProcessLists.cpp
  
  Description:
   Function definitions for the sortProcessLists.hpp file.

   The current solution sorts by the list type (PID, USER, PR...).  The algorithms
   determine the significant values and places them in descending order.  If there
   is a duplicate value, it sorts those by PID in ascending order. This pattern
   is repeated until all lists are sorted(although the algorithm doesn't 
   necessarily operate systematically by the described  pattern, it is the
   result).
   
  Analysis:
   After quick analysis, while it looks as if it's nested loop is iterating over the size
   of types, it is iterating over the different value "types" found making the overall
   time complexity  O(N * Logn(N)), which is sufficient.
*/
#include "sortProcessLists.hpp"


template std::vector<int> sortObjectsByValue(
    const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
    const std::vector<int>& pidNums,
    const unsigned int& (ProcessInfo::*extractor)() const);


/*
  Function:
   sortByUSER

  Description:
   Sorts the pid list by USER.

  Input:
   allProcessInfo       - all stored process data that will be traversed in
                          ordere to retrieve desired sort state values

   pidNums              - a const reference to a PID list representing all running
                          processes

  Output:
   const std::vector<int>
                        - the sorted list of PIDs
 */
const std::vector<int> sortByUSER(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
				  const std::vector<int>& pidNums)
{
  std::vector<std::pair<std::string,int>> procUSERStrings;
  std::set<std::string> userTypes;
  std::vector<std::string> types;
  std::vector<int> tempPIDs;
  
  // get all std::pairs of <user, pid> and store them in vector
  for(int i = 0, j = 0; i < allProcessInfo.size(); i++)
    {
      procUSERStrings.push_back(std::make_pair(allProcessInfo.at(pidNums.at(i))->getUSER(),
					       pidNums.at(i)));

      // get the different user types (repeated values for separating later)
      if(userTypes.count(procUSERStrings.at(i).first) == 0)
	{
	  userTypes.insert(procUSERStrings.at(i).first);
	}
    }

  // save user types as vector of string for later use
  for(std::set<std::string>::iterator it = userTypes.begin();
      it != userTypes.end(); it++)
    {
      types.push_back(*it);
    }
  
  // store all PIDS as a vector of vector of std::pair<int, USER>
  std::vector<std::vector<std::pair<int, std::string>>> sortedByUserTypePID(types.size());
  for(int i = 0; i < procUSERStrings.size(); i++)
    {
      for(int j = 0; j < types.size(); j++)
	{
	  if(types.at(j) == procUSERStrings.at(i).first)
	    {
	      sortedByUserTypePID[j].push_back(std::make_pair(procUSERStrings.at(i).second,
							      procUSERStrings.at(i).first));
	    }
	}
    }

  // sort each user type list by PID
  for(int i = 0; i < sortedByUserTypePID.size(); i++)
    {
      std::sort(sortedByUserTypePID.at(i).begin(), sortedByUserTypePID.at(i).end());
    }

  // store the list of sorted PIDs to vector<int> to return to caller 
  for(int i = 0; i < sortedByUserTypePID.size(); i++)
    {
      for(int j = 0; j < sortedByUserTypePID.at(i).size(); j++)
	{
	  tempPIDs.push_back(sortedByUserTypePID.at(i).at(j).first);
	}
    }
  
  return tempPIDs;
} // end of "sortByUSER"



template <typename T>
std::vector<int> sortObjectsByValue
(const std::unordered_map<int, T*>& allProcessInfo,
 const std::vector<int>& pidNums,
 const unsigned int& (T::*extractor)() const)
{
  std::vector<std::pair<int, int>> procPR;
  std::set<int> intTypes;
  std::vector<int> types;
  std::vector<int> tempPIDs;  

  for (int i = 0; i < allProcessInfo.size(); i++)
    {

      int pid = pidNums[i];
      int value = (allProcessInfo.at(pid)->*extractor)();  
      procPR.push_back(std::make_pair(value, pid));

    
      // get the different PR types (repeated values for separating later)
      if(intTypes.count(procPR.at(i).first) == 0)
	{
	  intTypes.insert(procPR.at(i).first);
	}
    }
    
  // save PR types as vector of string for later use
  for(std::set<int>::iterator it = intTypes.begin();
      it != intTypes.end(); it++)
    {
      types.push_back(*it);
    }
  
  // store all PIDS as a vector of vector of std::pair<PID, PR>
  std::vector<std::vector<std::pair<int, int>>> sortedByPRTypePID(types.size());
  for(int i = 0; i < procPR.size(); i++)
    {
      for(int j = 0; j < types.size(); j++)
	{
	  if(types.at(j) == procPR.at(i).first)
	    {
	      sortedByPRTypePID[j].push_back(std::make_pair(procPR.at(i).second,
							    procPR.at(i).first));
	    }
	}
    }
  
  // sort each PR type list by PID
  for(int i = 0; i < sortedByPRTypePID.size(); i++)
    {
      std::sort(sortedByPRTypePID.at(i).begin(), sortedByPRTypePID.at(i).end());
    }

  // store the list of sorted PIDs to vector<int> to return to caller 
  for(int i = sortedByPRTypePID.size() - 1; i >= 0; i--)    
    {
      for(int j = 0; j < sortedByPRTypePID.at(i).size(); j++)
	{
	  tempPIDs.push_back(sortedByPRTypePID.at(i).at(j).first);
	}
    }

  return tempPIDs;
}



/*
  Function:
   sortByS

  Description:
   Sorts the pid list by S.

  Input:
   allProcessInfo             - all stored process data that will be traversed in
                          ordere to retrieve desired sort state values

   pidNums              - a const reference to a PID list representing all running
                          processes

  Output:
   const std::vector<int>
                        - the sorted list of PIDs
*/
const std::vector<int> sortByS(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			       const std::vector<int>& pidNums)
{
  std::vector<std::pair<std::string,int>> procStrings;
  std::set<std::string> STypes;
  std::vector<std::string> types;
  std::vector<int> tempPIDs;
  
  // get all std::pairs of <S, pid> and store them in vector
  for(int i = 0, j = 0; i < allProcessInfo.size(); i++)
    {
      procStrings.push_back(std::make_pair(std::to_string(allProcessInfo.at(pidNums.at(i))->getS()),
					   pidNums.at(i)));

      // get the different S types (repeated values for separating later)
      if(STypes.count(procStrings.at(i).first) == 0)
	{
	  STypes.insert(procStrings.at(i).first);
	}
    }

  // save S types as vector of string for later use
  for(std::set<std::string>::iterator it = STypes.begin();
      it != STypes.end(); it++)
    {
      types.push_back(*it);
    }
  
  // store all PIDS as a vector of vector of std::pair<int, S>
  std::vector<std::vector<std::pair<int, std::string>>> sortedBySTypePID(types.size());
  for(int i = 0; i < procStrings.size(); i++)
    {
      for(int j = 0; j < types.size(); j++)
	{
	  if(types.at(j) == procStrings.at(i).first)
	    {
	      sortedBySTypePID[j].push_back(std::make_pair(procStrings.at(i).second,
							   procStrings.at(i).first));
	    }
	}
    }

  // sort each S type list by PID
  for(int i = 0; i < sortedBySTypePID.size(); i++)
    {
      std::sort(sortedBySTypePID.at(i).begin(), sortedBySTypePID.at(i).end());
    }

  // store the list of sorted PIDs to vector<int> to return to caller 
  for(int i = 0; i < sortedBySTypePID.size(); i++)
    {
      for(int j = 0; j < sortedBySTypePID.at(i).size(); j++)
	{
	  tempPIDs.push_back(sortedBySTypePID.at(i).at(j).first);
	}
    }
  
  return tempPIDs;
}  // end of "sortByS"



/*
  Function:
   sortByCPUUsage

  Description:
   Sorts the pid list in descending order of the highest current CPU usage of
   the allocated processes.

  Input:
   allProcessInfo             - all stored process data that will be traversed in
                          ordere to retrieve desired sort state values

   pidNums              - a const reference to a PID list representing all running
                          processes

  Output:
   const std::vector<int>
                        - the sorted list of PIDs
*/
const std::vector<int> sortByCPUUsage(const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
				      const std::vector<int>& pidNums)
{
  std::vector<std::pair<double,int>> procCPUUsage;
  std::set<double> intTypes;
  std::vector<double> types;
  std::vector<int> tempPIDs;
  
  // get all std::pairs of <CPUUsage, pid> and store them in vector
  for(int i = 0, j = 0; i < allProcessInfo.size(); i++)
    {
      procCPUUsage.push_back(std::make_pair(allProcessInfo.at(pidNums.at(i))->getCPUUsage(),
					    pidNums.at(i)));

      // get the different CPUUsage types (repeated values for separating later)
      if(intTypes.count(procCPUUsage.at(i).first) == 0)
	{
	  intTypes.insert(procCPUUsage.at(i).first);
	}
    }

  // save CPUUsage types as vector of double for later use
  for(std::set<double>::iterator it = intTypes.begin();
      it != intTypes.end(); it++)
    {
      types.push_back(*it);
    }
  
  // store all PIDS as a vector of vector of std::pair<PID, CPUUsage>
  std::vector<std::vector<std::pair<int, double>>> sortedByCPUUsageTypePID(types.size());
  for(int i = 0; i < procCPUUsage.size(); i++)
    {
      for(int j = 0; j < types.size(); j++)
	{
	  if(types.at(j) == procCPUUsage.at(i).first)
	    {
	      sortedByCPUUsageTypePID[j].push_back(std::make_pair(procCPUUsage.at(i).second,
							      procCPUUsage.at(i).first));
	    }
	}
    }
  
  // sort each CPUUsage types list by PID
  for(int i = 0; i < sortedByCPUUsageTypePID.size(); i++)
    {
      std::sort(sortedByCPUUsageTypePID.at(i).begin(), sortedByCPUUsageTypePID.at(i).end());
    }

  // store the list of sorted PIDs to vector<int> to return to caller 
  for(int i = sortedByCPUUsageTypePID.size() - 1; i >= 0; i--)    
    {
      for(int j = 0; j < sortedByCPUUsageTypePID.at(i).size(); j++)
	{
	  tempPIDs.push_back(sortedByCPUUsageTypePID.at(i).at(j).first);
	}
    }
  
  return tempPIDs;
} // end of "sortByCPUUsage"



/*
  Function:
   sortByMEMUsage

  Description:
   Sorts the pid list in descending order of the highest current memory usage of
   the allocated processes.  


  Input:
   allProcessInfo             - all stored process data that will be traversed in
                          ordere to retrieve desired sort state values

   pidNums              - a const reference to a PID list representing all running
                          processes

  Output:
   const std::vector<int>
                        - the sorted list of PIDs
*/
const std::vector<int> sortByMEMUsage(const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
				      const std::vector<int>& pidNums)
{
  std::vector<std::pair<double,int>> procMEMUsage;
  std::set<double> intTypes;
  std::vector<double> types;
  std::vector<int> tempPIDs;
  
  // get all std::pairs of <MEMUsage, pid> and store them in vector
  for(int i = 0, j = 0; i < allProcessInfo.size(); i++)
    {
      procMEMUsage.push_back(std::make_pair(allProcessInfo.at(pidNums.at(i))->getMEMUsage(),
					    pidNums.at(i)));

      // get the different MEMUsage types (repeated values for separating later)
      if(intTypes.count(procMEMUsage.at(i).first) == 0)
	{
	  intTypes.insert(procMEMUsage.at(i).first);
	}
    }

  // save MEMUsage types as vector of double for later use
  for(std::set<double>::iterator it = intTypes.begin();
      it != intTypes.end(); it++)
    {
      types.push_back(*it);
    }
  
  // store all PIDS as a vector of vector of std::pair<PID, MEMUsage>
  std::vector<std::vector<std::pair<int, double>>> sortedByMEMUsageTypePID(types.size());
  for(int i = 0; i < procMEMUsage.size(); i++)
    {
      for(int j = 0; j < types.size(); j++)
	{
	  if(types.at(j) == procMEMUsage.at(i).first)
	    {
	      sortedByMEMUsageTypePID[j].push_back(std::make_pair(procMEMUsage.at(i).second,
							      procMEMUsage.at(i).first));
	    }
	}
    }
  
  // sort each MEMUsage types list by PID
  for(int i = 0; i < sortedByMEMUsageTypePID.size(); i++)
    {
      std::sort(sortedByMEMUsageTypePID.at(i).begin(), sortedByMEMUsageTypePID.at(i).end());
    }

  // store the list of sorted PIDs to vector<int> to return to caller 
  for(int i = sortedByMEMUsageTypePID.size() - 1; i >= 0; i--)    
    {
      for(int j = 0; j < sortedByMEMUsageTypePID.at(i).size(); j++)
	{
	  tempPIDs.push_back(sortedByMEMUsageTypePID.at(i).at(j).first);
	}
    }
  
  return tempPIDs;
} // end of "sortByMEMUsage"



/*
  Function:
   sortByCpuTime

  Description:
   Sorts the pid list in descending order of process CPU time.

  Input:
   allProcessInfo             - all stored process data that will be traversed in
                          ordere to retrieve desired sort state values

   pidNums              - a const reference to a PID list representing all running
                          processes

  Output:
   const std::vector<int>
                        - the sorted list of PIDs
 */
const std::vector<int> sortByCpuTime(const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
				      const std::vector<int>& pidNums)
{
  std::vector<std::pair<double,int>> procCpuTime;
  std::set<double> doubleTypes;
  std::vector<int> types;
  std::vector<int> tempPIDs;
  
  // get all std::pairs of <CpuTime, pid> and store them in vector
  for(int i = 0, j = 0; i < allProcessInfo.size(); i++)
    {
      procCpuTime.push_back(std::make_pair(allProcessInfo.at(pidNums.at(i))->getCpuRawTime(),
					pidNums.at(i)));

      // get the different CpuTime types (repeated values for separating later)
      if(doubleTypes.count(procCpuTime.at(i).first) == 0)
	{
	  doubleTypes.insert(procCpuTime.at(i).first);
	}
    }

  // save CpuTime types as vector of string for later use
  for(std::set<double>::iterator it = doubleTypes.begin();
      it != doubleTypes.end(); it++)
    {
      types.push_back(*it);
    }
  
  // store all PIDS as a vector of vector of std::pair<PID, CpuTime>
  std::vector<std::vector<std::pair<int, int>>> sortedByCpuTimeTypePID(types.size());
  for(int i = 0; i < procCpuTime.size(); i++)
    {
      for(int j = 0; j < types.size(); j++)
	{
	  if(types.at(j) == procCpuTime.at(i).first)
	    {
	      sortedByCpuTimeTypePID[j].push_back(std::make_pair(procCpuTime.at(i).second,
							      procCpuTime.at(i).first));
	    }
	}
    }
  
  // sort each CpuTime type list by PID
  for(int i = 0; i < sortedByCpuTimeTypePID.size(); i++)
    {
      std::sort(sortedByCpuTimeTypePID.at(i).begin(), sortedByCpuTimeTypePID.at(i).end());
    }

  // store the list of sorted PIDs to vector<int> to return to caller 
  for(int i = sortedByCpuTimeTypePID.size() - 1; i >= 0; i--)    
    {
      for(int j = 0; j < sortedByCpuTimeTypePID.at(i).size(); j++)
	{
	  tempPIDs.push_back(sortedByCpuTimeTypePID.at(i).at(j).first);
	}
    }
  
  return tempPIDs;
} // end of "sortByCpuTime"



/*
  Function:
   sortByCOMMAND

  Description:
   Sorts the pid list by COMMAND.

  Input:
   allProcessInfo             - all stored process data that will be traversed in
                          ordere to retrieve desired sort state values

   pidNums              - a const reference to a PID list representing all running
                          processes

  Output:
   const std::vector<int>
                        - the sorted list of PIDs
*/
const std::vector<int> sortByCOMMAND(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
				     const std::vector<int>& pidNums)
{
  std::vector<std::pair<std::string,int>> procStrings;
  std::set<std::string> commandTypes;
  std::vector<std::string> types;
  std::vector<int> tempPIDs;
  
  // get all std::pairs of <COMMAND, pid> and store them in vector
  for(int i = 0, j = 0; i < allProcessInfo.size(); i++)
    {
      procStrings.push_back(std::make_pair(allProcessInfo.at(pidNums.at(i))->getCOMMAND(),
					   pidNums.at(i)));

      // get the different COMMAND types (repeated values for separating later)
      if(commandTypes.count(procStrings.at(i).first) == 0)
	{
	  commandTypes.insert(procStrings.at(i).first);
	}
    }

  // save command types as vector of string for later use
  for(std::set<std::string>::iterator it = commandTypes.begin();
      it != commandTypes.end(); it++)
    {
      types.push_back(*it);
    }
  
  // store all PIDS as a vector of vector of std::pair<int, COMMAND>
  std::vector<std::vector<std::pair<int, std::string>>> sortedByCOMMANDTypePID(types.size());
  for(int i = 0; i < procStrings.size(); i++)
    {
      for(int j = 0; j < types.size(); j++)
	{
	  if(types.at(j) == procStrings.at(i).first)
	    {
	      sortedByCOMMANDTypePID[j].push_back(std::make_pair(procStrings.at(i).second,
							      procStrings.at(i).first));
	    }
	}
    }

  // sort each COMMAND type list by PID
  for(int i = 0; i < sortedByCOMMANDTypePID.size(); i++)
    {
      std::sort(sortedByCOMMANDTypePID.at(i).begin(), sortedByCOMMANDTypePID.at(i).end());
    }

  // store the list of sorted PIDs to vector<int> to return to caller 
  for(int i = 0; i < sortedByCOMMANDTypePID.size(); i++)
    {
      for(int j = 0; j < sortedByCOMMANDTypePID.at(i).size(); j++)
	{
	  tempPIDs.push_back(sortedByCOMMANDTypePID.at(i).at(j).first);
	}
    }
  
  return tempPIDs;
} // end of "sortByCOMMAND"
