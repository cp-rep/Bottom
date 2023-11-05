/*
  File:
   sortProcessLists.hpp
  
  Description:
   Header file containing a function declaration for sorting allocated process
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

template <typename T>
std::vector<int> sortValuesByPID(const std::unordered_map<int, ProcessInfo*>& allProcessInfo,
				 const std::vector<int>& pidNums,
				 const T& (ProcessInfo::*extractor)() const);
#endif
