/*
  File:
   sortProcessLists.hpp
  
  Description:
   Header file containing function declarations for sorting allocated process
   data.
 */
#ifndef SORTPROCESSLISTS_HPP
#define SORTPROCESSLISTS_HPP
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
#include "processInfo.hpp"
#include "_cursesWinConsts.hpp"

const std::vector<int> sortByUSER(std::unordered_map<int, ProcessInfo*>& procData,
				  const std::vector<int>& pidNums);
const std::vector<int> sortByPR(const std::unordered_map<int, ProcessInfo*>& procData,
				 const std::vector<int>& pidNums);
const std::vector<int> sortByNI(const std::unordered_map<int, ProcessInfo*>& procData,
				 const std::vector<int>& pidNums);
const std::vector<int> sortByVIRT(const std::unordered_map<int, ProcessInfo*>& procData,
				  const std::vector<int>& pidNums);
const std::vector<int> sortByRES(const std::unordered_map<int, ProcessInfo*>& procData,
				 const std::vector<int>& pidNums);
const std::vector<int> sortBySHR(const std::unordered_map<int, ProcessInfo*>& procData,
				 const std::vector<int>& pidNums);
const std::vector<int> sortByS(std::unordered_map<int, ProcessInfo*>& procData,
			       const std::vector<int>& pidNums);
const std::vector<int> sortByCPUUsage(const std::unordered_map<int, ProcessInfo*>& procData,
				      const std::vector<int>& pidNums);
const std::vector<int> sortByMEMUsage(const std::unordered_map<int, ProcessInfo*>& procData,
				      const std::vector<int>& pidNums);
const std::vector<int> sortByCOMMAND(std::unordered_map<int, ProcessInfo*>& procData,
				     const std::vector<int>& pidNums);
#endif
