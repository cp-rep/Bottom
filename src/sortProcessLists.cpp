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
const std::vector<int> sortByUSER(const std::vector<int>& pidNums,
				  std::unordered_map<int, ProcessInfo*>& procData,
				  const int& listType)
{
  std::vector<std::pair<std::string,int>> procStrings;
  std::vector<std::vector<std::pair<std::string, int>>> sortedByUserTypePID;
  std::vector<int> tempPIDs;
  std::set<std::string> userTypes;

  userTypes.insert("root");

  // get all USERS and PIDS
  for(int i = 0; i < procData.size(); i++)
    {
      procStrings.push_back(std::make_pair(procData[pidNums.at(i)]->getUSER(),
					   pidNums.at(i)));
    }

  // sort them by user type
  std::sort(procStrings.begin(), procStrings.end());

  // sort
  for(int i = 0; i < procStrings.size(); i++)
    {
      tempPIDs.push_back(procStrings.at(i).second);
    }
  
  return tempPIDs;
} // end of "sortByUSER"
*/


/*
  Function:
  mergeDoubleLists

  Description:
  Merges two process lists.
  
  Input:
  frontList         - a const reference to a list of sorted double data types

  backList          - a const reference to the current entire process list

  pUmap             - a const reference to the entire list of processes including 
                      any that have died/closed

  Output:
  vector<int>       - the resulting merged list of process IDs
 */
const std::vector<int> mergeDoubleLists(const std::vector<std::pair<double, int>>& frontList,
					const std::vector<int>& backList,
					const std::unordered_map<int, ProcessInfo*>& pUmap)
{
  std::vector<int> tempList;
  
  for(int i = frontList.size() - 1; i >= 0; i--)
    {
      tempList.push_back(frontList.at(i).second);
    }

  for(int i = 0; i < pUmap.size(); i++)
    {
      bool isInArray = false;

      for(int j = 0; j < frontList.size(); j++)
	{
	  if(frontList.at(j).second == pUmap.at(backList.at(i))->getPID())
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

  pUmap             - a const reference to the entire list of processes including 
                      any that have died/closed

  Output:
  vector<int>       - the resulting merged list of process IDs
 */
const std::vector<int> mergeIntLists(const std::vector<std::pair<int, int>>& frontList,
				    const std::vector<int>& backList,
				    const std::unordered_map<int, ProcessInfo*>& pUmap)
{
  std::vector<int> tempList;

  for(int i = frontList.size() - 1; i >= 0; i--)
    {
      tempList.push_back(frontList.at(i).second);
    }  
  
  for(int i = 0; i < pUmap.size(); i++)
    {
      bool isInArray = false;

      for(int j = 0; j < frontList.size(); j++)
	{
	  if(frontList.at(j).second == pUmap.at(backList.at(i))->getPID())
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

  Merges two process lists.
  
  Input:
  frontList         - a const reference to a list of sorted string data types

  backList          - a const reference to the current entire process list

  pUmap             - a const reference to the entire list of processes including 
                      any that have died/closed

  Output:
  vector<int>       - the resulting merged list of process IDs
 */
const std::vector<int> mergeStringLists(const std::vector<std::pair<std::string,
					int>>& frontList,
					const std::vector<int>& backList,
					const std::unordered_map<int, ProcessInfo*>& pUmap)
{
  std::vector<int> tempList;

  for(int i = frontList.size() - 1; i >= 0; i--)
    {
      tempList.push_back(frontList.at(i).second);
    }
  
  for(int i = 0; i < pUmap.size(); i++)
    {
      bool isInArray = false;

      for(int j = 0; j < frontList.size(); j++)
	{
	  if(frontList.at(j).second == pUmap.at(backList.at(i))->getPID())
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



/*
  Description:
  Stores related data corresponding to the desired sort state and
  returns it to the caller.


  Input:
  
  pidNums               - a const reference to a PID list representing all running
                          processes

  procData              - all stored process data that will be traversed in
                          ordere to retrieve desired sort state values

  sortState             - a const reference to the sort state the program will
                          be switching to.  It is used here as a switch statement
			  value to determine which set of data to return to the
			  caller.

  Output:

  const std::vector<std::pair<std::string, int>>
                        - the list of <string, int> pairs that is the string
			  to sort by and it's corresponding process ID
*/
const std::vector<std::pair<std::string, int>> getProcStrs
(const std::vector<int>& pidNums,
 std::unordered_map<int, ProcessInfo*>& procData,
 const int& listType)
{
  std::vector<std::pair<std::string, int>> tempStrings;
  std::string temp;

  // retrieve the desired corresponding processes data string
  switch(listType)
    {
    case _PIDWIN:
      break;
    case _USERWIN:
      break;
    case _PRWIN:
      break;
    case _NIWIN:
      break;
    case _VIRTWIN:
      break;
    case _RESWIN:
      break;
    case _SHRWIN:
      break;
    case _SWIN:
      break;
    case _PROCCPUWIN:
      break;
    case _PROCMEMWIN:
      break;
    case _PROCTIMEWIN:
      break;
    case _COMMANDWIN:
      break;
    default:
      break;
    }


  return tempStrings;
} // end of "retrieveProcDataStrs"



