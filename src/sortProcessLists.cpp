/*
  File: sortProcessLists.cpp
  
  Description:
  Function implementations for sortProcessList.  These functions are used by main.cpp
  to combine PID lists and return a merged sorted lists while checking for duplicates.

  Notes:
  Brute Force Solution to output Sorted Process Data:
  - sort all of the data
  - for all duplicates, sort them by PID
  - concatenate/append them to an output list according to required list hierarchy
*/
#include "sortProcessLists.hpp"



/*
  Function:
   sortByUSER

  Description:
   Updates the PID list that is used for printing process data to the screen.
   It sorts the pid list by USER. First it separates users into their own lists,
   then it sorts those lists by their contained PIDS.  That final sorted list list
   is then copied to an output list and returned to the caller.  Ultimately, it's
   an O(N^2) algorithm determined by number of running processes and number of
   users.

  Input:
   procData             - all stored process data that will be traversed in
                          ordere to retrieve desired sort state values

   pidNums              - a const reference to a PID list representing all running
                          processes

  Output:
   const std::vector<int>
                        - the sorted list of PIDs
 */
const std::vector<int> sortByUSER(std::unordered_map<int, ProcessInfo*>& procData,
				  const std::vector<int>& pidNums)
{
  std::vector<std::pair<std::string,int>> procStrings;
  std::set<std::string> userTypes;
  std::vector<std::string> types;
  std::vector<int> tempPIDs;
  
  // get all std::pairs of <user, pid> and store them in vector
  for(int i = 0, j = 0; i < procData.size(); i++)
    {
      procStrings.push_back(std::make_pair(procData.at(pidNums.at(i))->getUSER(),
					   pidNums.at(i)));

      // get the different user types
      if(userTypes.count(procStrings.at(i).first) == 0)
	{
	  userTypes.insert(procStrings.at(i).first);
	}
    }

  // ignore unwated user type while saving user types as vector of string for later use
  for(std::set<std::string>::iterator it = userTypes.begin();
      it != userTypes.end(); it++)
    {
      // bandaid for the current pipe process "bug"
      if(*it != "-1")
	{
	  types.push_back(*it);
	}
    }
  
  // store all PIDS as a vector of vector of std::pair<int, user>
  std::vector<std::vector<std::pair<int, std::string>>> sortedByUserTypePID(types.size());
  for(int i = 0; i < procStrings.size(); i++)
    {
      for(int j = 0; j < types.size(); j++)
	{
	  if(types.at(j) == procStrings.at(i).first)
	    {
	      sortedByUserTypePID[j].push_back(std::make_pair(procStrings.at(i).second,
							      procStrings.at(i).first));
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



/*
  Function:
   sortByNI

  Description:
   Sorts and returns the PID list by NI.

  Input:
   procData             - a const reference to the entire list of processes and their data.

   pidNums              - a const reference to a PID list representing all running
                          processes

  Output:
   vector<int>          - the resulting merged list of process IDs
 */
const std::vector<int> sortByNI(const std::unordered_map<int, ProcessInfo*>& procData,
				const std::vector<int>& pidNums)
{
  std::vector<std::pair<int, int>> sortedByInt;
  std::vector<int> tempPIDs;
  
  for(int i = 0; i < procData.size(); i++)
    {
      // get NI int value
      const int tempInt = procData.at(pidNums.at(i))->getNI();

      // store NI value with pid in vector<pair(NI, PID)>
      sortedByInt.push_back(std::make_pair(tempInt, pidNums.at(i)));
    }

  // sort vector by NI val
  std::sort(sortedByInt.begin(), sortedByInt.end());

  // save merged sorted list
  tempPIDs = mergeIntLists(sortedByInt,
			   pidNums,
			   procData);

  // return sorted PIDS
  return tempPIDs;
} // end of "sortByNI"



/*
  Function:
   sortByVIRT

  Description:
   Sorts and returns the PID list by VIRT.
  
  Input:
   procData             - a const reference to the entire list of processes and their data.

  Output:
   vector<int>          - the resulting merged list of process IDs
 */
const std::vector<int> sortByVIRT(const std::unordered_map<int, ProcessInfo*>& procData,
				  const std::vector<int>& pidNums)
{
  std::vector<std::pair<int, int>> sortedByInt;
  std::vector<int> tempPIDs;
  
  for(int i = 0; i < procData.size(); i++)
    {
      const int tempInt = procData.at(pidNums.at(i))->getVIRT();
      sortedByInt.push_back(std::make_pair(tempInt, pidNums.at(i)));
    }

  std::sort(sortedByInt.begin(), sortedByInt.end());
  tempPIDs = mergeIntLists(sortedByInt,
			   pidNums,
			   procData);
  
  return tempPIDs;
} // end of "sortByVIRT"



/*
  Function:
   sortByRES

  Description:
   Sorts and returns the PID list by RES.
  
  Input:
   procData             - a const reference to the entire list of processes and their data.

   pidNums              - a const reference to a PID list representing all running
                          processes
		      
  Output:
   vector<int>          - the resulting merged list of process IDs
 */
const std::vector<int> sortByRES(const std::unordered_map<int, ProcessInfo*>& procData,
				 const std::vector<int>& pidNums)
{
  std::vector<std::pair<int, int>> sortedByInt;
  std::vector<int> tempPIDs;
  
  for(int i = 0; i < procData.size(); i++)
    {
      const int tempInt = procData.at(pidNums.at(i))->getRES();
      sortedByInt.push_back(std::make_pair(tempInt, pidNums.at(i)));
    }

  std::sort(sortedByInt.begin(), sortedByInt.end());
  tempPIDs = mergeIntLists(sortedByInt,
			   pidNums,
			   procData);
  
  return tempPIDs;
} // end of "sortByRES'



/*
  Function:
   sortBySHR

  Description:
   Sorts and returns the PID list by SHR.
  
  Input:
   procData             - a const reference to the entire list of processes and their data.

   pidNums              - a const reference to a PID list representing all running
                          processes

  Output:
   vector<int>          - the resulting merged list of process IDs
 */
const std::vector<int> sortBySHR(const std::unordered_map<int, ProcessInfo*>& procData,
				 const std::vector<int>& pidNums)
{
  std::vector<std::pair<int, int>> sortedByInt;
  std::vector<int> tempPIDs;
  
  for(int i = 0; i < procData.size(); i++)
    {
      const int tempInt = procData.at(pidNums.at(i))->getSHR();
      sortedByInt.push_back(std::make_pair(tempInt, pidNums.at(i)));
    }

  std::sort(sortedByInt.begin(), sortedByInt.end());
  tempPIDs = mergeIntLists(sortedByInt,
			   pidNums,
			   procData);
  
  return tempPIDs;
} // end of "sortBySHR"



/*
  Function:
   sortByS

  Description:
   Sorts and returns the PID list by S.
  
  Input:
   procData             - a const reference to the entire list of processes and their data.

   pidNums              - a const reference to a PID list representing all running
                          processes

  Output:
   vector<int>          - the resulting merged list of process IDs
 */
const std::vector<int> sortByS(const std::unordered_map<int, ProcessInfo*>& procData,
			       const std::vector<int>& pidNums)
{
  std::vector<std::pair<std::string, int>> sortedByStr;
  std::vector<int> tempPIDs;
  
  for(int i = 0; i < procData.size(); i++)
    {
      const std::string tempStr = std::to_string(procData.at(pidNums.at(i))->getS());
      sortedByStr.push_back(std::make_pair(tempStr, pidNums.at(i)));
    }

  std::sort(sortedByStr.begin(), sortedByStr.end());
  tempPIDs = mergeStringLists(sortedByStr,
			      pidNums,
			      procData);
  
  return tempPIDs;
} // end of "sortByS"



/*
  Function:
  mergeDoubleLists

  Description:
  Merges two process lists.
  
  Input:
  frontList         - a const reference to a list of sorted double data types

  backList          - a const reference to the current entire process list

  procData             - a const reference to the entire list of processes including 
                      any that have died/closed

  Output:
  vector<int>       - the resulting merged list of process IDs
 */
const std::vector<int> mergeDoubleLists(const std::vector<std::pair<double, int>>& frontList,
					const std::vector<int>& backList,
					const std::unordered_map<int, ProcessInfo*>& procData)
{
  std::vector<int> tempList;
  
  for(int i = frontList.size() - 1; i >= 0; i--)
    {
      tempList.push_back(frontList.at(i).second);
    }

  for(int i = 0; i < procData.size(); i++)
    {
      bool isInArray = false;

      for(int j = 0; j < frontList.size(); j++)
	{
	  if(frontList.at(j).second == procData.at(backList.at(i))->getPID())
	    {
	      isInArray = true;
	      break;
	    }
	}
      
      if(isInArray == false)
	{
	  tempList.push_back(backList.at(i));
	}
    }

  return tempList;
} // end of "mergeDoubleLists"



/*
  Function:
  mergeIntLists

  Merges two process lists.
  
  Input:
  frontList         - a const reference to a list of sorted int data types

  backList          - a const reference to the current entire process list

  procData             - a const reference to the entire list of processes including 
                      any that have died/closed

  Output:
  vector<int>       - the resulting merged list of process IDs
 */
const std::vector<int> mergeIntLists(const std::vector<std::pair<int, int>>& frontList,
				    const std::vector<int>& backList,
				    const std::unordered_map<int, ProcessInfo*>& procData)
{
  std::vector<int> tempList;

  for(int i = frontList.size() - 1; i >= 0; i--)
    {
      tempList.push_back(frontList.at(i).second);
    }  
  
  for(int i = 0; i < procData.size(); i++)
    {
      bool isInArray = false;

      for(int j = 0; j < frontList.size(); j++)
	{
	  if(frontList.at(j).second == procData.at(backList.at(i))->getPID())
	    {
	      isInArray = true;
	    }
	}
      
      if(isInArray == false)
	{
	  tempList.push_back(backList.at(i));
	}
    }
  
  return tempList;
} // end of "mergeIntLists"



/*
  Function:
  mergeStringLists

  Description:
   A helper function that merges two sorted lists.
  
  Input:
  frontList         - a const reference to a list of sorted string data types

  backList          - a const reference to the current entire process list

  procData             - a const reference to the entire list of processes including 
                      any that have died/closed

  Output:
  vector<int>       - the resulting merged list of process IDs
 */
const std::vector<int> mergeStringLists(const std::vector<std::pair<std::string,
					int>>& frontList,
					const std::vector<int>& backList,
					const std::unordered_map<int, ProcessInfo*>& procData)
{
  std::vector<int> tempList;

  for(int i = frontList.size() - 1; i >= 0; i--)
    {
      tempList.push_back(frontList.at(i).second);
    }
  
  for(int i = 0; i < procData.size(); i++)
    {
      bool isInArray = false;

      for(int j = 0; j < frontList.size(); j++)
	{
	  if(frontList.at(j).second == procData.at(backList.at(i))->getPID())
	    {
	      isInArray = true;
	    }
	}
      if(isInArray == false)
	{
	  tempList.push_back(backList.at(i));
	}
    }

  return tempList;
} // end of "mergeStringLists"
