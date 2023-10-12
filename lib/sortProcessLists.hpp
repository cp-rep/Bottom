/*
  File: sortProcessLists.hpp
  
  Description:
  Header file for function declarations for PID list sorting functions
 */
#ifndef SORTPROCESSLISTS_HPP
#define SORTPROCESSLISTS_HPP
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "processInfo.hpp"
#include "cursesWinConsts.hpp"

const std::vector<int> mergeDoubleLists(const std::vector<std::pair<double, int>>& frontList,
					const std::vector<int>& backList,
					const std::unordered_map<int, ProcessInfo*>& pUmap);
const std::vector<int> mergeIntLists(const std::vector<std::pair<int, int>>& frontList,
				     const std::vector<int>& backList,
				     const std::unordered_map<int, ProcessInfo*>& pUmap);
const std::vector<int> mergeStringLists(const std::vector<std::pair<std::string, int>>& frontList,
					const std::vector<int>& backList,
					const std::unordered_map<int, ProcessInfo*>& pUmap);

const std::vector<std::pair<std::string, int>> retrievePRStrings
(const std::vector<int>& pidNums,
 std::unordered_map<int, ProcessInfo*>& procData,
 const int& listType);

#endif
