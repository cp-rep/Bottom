/*
  File: cursesWrappers.hpp
*/
#ifndef CURSESWRAPPERS_HPP
#define CURSESWRAPPERS_HPP
#include <curses.h>
#include <vector>
#include <unordered_map>
#include "cursesColors.hpp"
#include "cursesWindow.hpp"
#include "processInfo.hpp"
#include "extractFileData.hpp"
#include "procStates.hpp"

void attronBottomWins(const std::vector<CursesWindow*>& wins,
		      int attrs);
void attroffBottomWins(const std::vector<CursesWindow*>& wins,
		       int attrs);
void clearBottomWins(const std::vector<CursesWindow*>& wins);
void printWindowNames(const std::vector<CursesWindow*>& wins);
void printProcs(const int& shiftY,
		const std::vector<int>& pidList,
		const std::unordered_map<int, ProcessInfo*>& pUmap,
		const std::vector<CursesWindow*>& wins);
void printSortedProcs(const std::vector<int>& pidList,
		      const std::vector<std::pair<double, int>>& sortedOut,
		      const std::unordered_map<int, ProcessInfo*>& pUmap,
		      const std::vector<CursesWindow*>& wins);
void printSortedProcsReverse(const int& startLine,
			     const std::vector<std::pair<double, int>>& sortedOut,
			     const std::unordered_map<int, ProcessInfo*>& pUmap,
			     const std::vector<CursesWindow*>& wins);
const std::string createColorLine(const int& len);
void printColorLine(const std::vector<CursesWindow*>& wins,
		    const std::vector<int>& winNums,
		    const std::string& colorLine,
		    const int& row,
		    const int& attrs);
#endif
