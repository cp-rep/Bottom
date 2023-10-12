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
  sortByString

  Description:
  After the list is sorted, all duplicate data will be moved to their own lists.
  The duplicate data lists will be sorted by PID. After all lists are sorted
  accordingly, they will be merged into one list based upon desired output
  hierarchy.
  
  Input:

  std::vector<int> pidNums; // to be populated with all current /proc/[pid] numbers
  std::unordered_map<int, ProcessInfo*> procData; // to be populated with /proc/[pid] data

  pidNums indexes into procData
  
  Output:
 */
void sortByString(const std::vector<int>& processIds,
		  const std::unordered_map<int, ProcessInfo*> procData)
{
  
} // end of "sortByString"



/*
void sortByString()
{
}


void sortByInt()
{
}


void sortByDouble()
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
  std::vector<int> pidNums; // to be populated with all current /proc/[pid] numbers
  std::unordered_map<int, ProcessInfo*> procData; // to be populated with /proc/[pid] data
  std::vector<std::pair<std::string, int>> sortedByString;
*/
const std::vector<std::pair<std::string, int>> retrievePRStrings
(const std::vector<int>& pidNums,
 std::unordered_map<int, ProcessInfo*>& procData,
 const int& listType)
{
  //  std::string temp;
  std::vector<std::pair<std::string, int>> tempStrings;
  std::string temp;
  
  for(int i = 0; i < procData.size(); i++)
    {
      switch(listType)
	{
	case _USERWIN:
	  break;
	case _PRWIN:
	    temp = procData[pidNums.at(i)]->getPR();
	    tempStrings.push_back(std::make_pair(temp, pidNums.at(i)));
	  break;
	case _SWIN:
	  break;
	case _COMMANDWIN:
	  break;
	case _PROCTIMEWIN:
	  break;
	default:
	  break;
	}
      
      tempStrings.push_back(std::make_pair(temp, pidNums.at(i)));
    }

  std::sort(tempStrings.begin(), tempStrings.end());

  return tempStrings;
} // end of "retrieveProcDataStrs"
