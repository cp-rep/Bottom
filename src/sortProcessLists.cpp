/*
  File: sortProcessLists.cpp
  
  Description:
   Function implementation for the sortProcessLists.hpp.
*/
#include "sortProcessLists.hpp"



/*
  Function:
   sortValuesByPID  

  Description:
   A template function that allows sorting the process data by any of the columns:
   - PID, USER, PR, NI, VIRT, RES, SHR, S, %CPU, %MEM, TIME+, COMMAND -.
   It determines what "getter" function the caller is using to return an object
   from the ProcessInfo class, and that object is stored in the typename T
   parameter.

   Each returned T object is stored in a vector with its corresponding PID value.
   The algorithm determines which objects have the same values and groups them up
   accordingly.  Each value list is then sorted by PID creating lists of the same
   value type sorted by their corresponding PIDs.  These different lists are then
   combined into a single list of PID numbers and then returned to the caller.

  Runtime Complexity:
   O(N * Log(N))

  Input:
   allProcessInfo       - all stored process data that will be traversed in
                          ordere to retrieve desired sort state values

   pidNums              - a const reference to a PID list representing all running
                          processes

   const T& (P::*extractor)() const
                        - A lambda function that uses two template parameters
			  to return different types that need sorting from
			  the ProcessInfo class. P template typename represents the
			  ProcessInfo class type that is necessary for he extractor
			  to call the classes different "getter" functions. The
			  T template typename allows the storing of the different
			  object types that are returned from the extractor.
  Output:
   const std::vector<int>
                        - the sorted list of PIDs
*/
template std::vector<int> sortValuesByPID(
    const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
    const std::vector<int>& pidNums,
    const unsigned int& (ProcessInfo::*extractor)() const);

template std::vector<int> sortValuesByPID(
    const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
    const std::vector<int>& pidNums,
    const std::string& (ProcessInfo::*extractor)() const);

template std::vector<int> sortValuesByPID(
    const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
    const std::vector<int>& pidNums,
    const double& (ProcessInfo::*extractor)() const);

template std::vector<int> sortValuesByPID(
    const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
    const std::vector<int>& pidNums,
    const char& (ProcessInfo::*extractor)() const);

template <typename P, typename T>
std::vector<int> sortValuesByPID(const std::unordered_map<int, P*>& allProcessInfo,
				 const std::vector<int>& pidNums,
				 const T& (P::*extractor)() const)
{
  std::vector<int> tempPIDs;  
  std::vector<std::pair<T, int>> tPid;
  std::set<T> diffValuesSet;
  typename std::set<T>::iterator it;
  std::vector<T> diffValuesVec;    

  T value;

  // loop through the ProcessInfo object and store all <key(PID), value(T)> pairs
  // in vector tPid as pairs of <T, PID>
  for(int i = 0; i < allProcessInfo.size(); i++)
    {
      value = (allProcessInfo.at(pidNums.at(i))->*extractor)();
      tPid.push_back(std::make_pair(value, pidNums.at(i)));

      // get the different T type values (repeated values for separating later)
      if(diffValuesSet.count(tPid.at(i).first) == 0)
	{
	  diffValuesSet.insert(tPid.at(i).first);
	}
    }

  // store the different types of T values in vector for easier use later
  for(it = diffValuesSet.begin(); it != diffValuesSet.end(); it++)
    {
      diffValuesVec.push_back(*it);
    }

  // create object to store all PIDS as a vector of vector of std::pair<PID, T>
  std::vector<std::vector<std::pair<int, T>>> sortedValuesByPID(diffValuesVec.size());

  // loop and store the values
  for(int i = 0; i < tPid.size(); i++)
    {
      for(int j = 0; j < diffValuesVec.size(); j++)
	{
	  if(diffValuesVec.at(j) == tPid.at(i).first)
	    {
	      sortedValuesByPID[j].push_back(std::make_pair(tPid.at(i).second,
							    tPid.at(i).first));
	    }
	}
    }

  // sort each group of T values by PID
  for(int i = 0; i < sortedValuesByPID.size(); i++)
    {
      std::sort(sortedValuesByPID.at(i).begin(), sortedValuesByPID.at(i).end());
    }

  // store the list of sorted PIDs to vector<int> to return to caller
  for(int i = sortedValuesByPID.size() - 1; i >= 0; i--)    
    {
      for(int j = 0; j < sortedValuesByPID.at(i).size(); j++)
	{
	  tempPIDs.push_back(sortedValuesByPID.at(i).at(j).first);
	}
    }

  return tempPIDs;
} // end of "sortValuesByPID"
