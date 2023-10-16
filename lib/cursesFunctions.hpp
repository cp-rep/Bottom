/*
  File:
   cursesFunctions.hpp

  Description:
   A collection of function declarations for manipulating CursesWindow objects.
   This includes creating, deleting, moving, and sorting the WINDOWs or their
   data.  Some functions for making necessary related calculations are
   also included.
*/
#ifndef CURSESFUNCTIONS_HPP
#define CURSESFUNCTIONS_HPP
#include <curses.h>
#include <vector>
#include <unordered_map>
#include "cursesColors.hpp"
#include "cursesWindow.hpp"
#include "processInfo.hpp"
#include "extractFileData.hpp"
#include "_progStateConsts.hpp"
#include "_cursesWinConsts.hpp"

void refreshAllWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearAllWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearTopWins(const std::unordered_map<int, CursesWindow*>& wins);
void clearBottomWins(const std::unordered_map<int, CursesWindow*>& wins);
void attronBottomWins(const std::unordered_map<int, CursesWindow*>& wins,
		      int attrs);
void attroffBottomWins(const std::unordered_map<int, CursesWindow*>& wins,
		       int attrs);
void printTopWins(const std::unordered_map<int, CursesWindow*>& wins,
		  const std::vector<std::string> outLines);
void printWindowNames(const std::unordered_map<int, CursesWindow*>& wins);
void printSortedProcs(const std::vector<int>& pidList,
		      const std::vector<std::pair<double, int>>& sortedOut,
		      const std::unordered_map<int, ProcessInfo*>& pUmap,
		      const std::unordered_map<int, CursesWindow*>& wins);
void printSortedProcsReverse(const int& startLine,
			     const std::vector<std::pair<double, int>>& sortedOut,
			     const std::unordered_map<int, ProcessInfo*>& pUmap,
			     const std::unordered_map<int, CursesWindow*>& wins);
const std::string createColorLine(const int& len);
void printProcs(const std::unordered_map<int, CursesWindow*>& wins,
		const std::unordered_map<int, ProcessInfo*>& pUmap,
		const std::vector<int>& pidList,
		const int& shiftY,
		const int& shiftX);
void printColorLine(const std::unordered_map<int, CursesWindow*>& wins,
		    const int& row,
		    const int& attrs,
		    const int& window,
		    const std::string& colorLine);
void shiftBottomWinsLeft(std::unordered_map<int, CursesWindow*>& wins,
			 const int& shiftX);
void shiftBottomWinsRight(std::unordered_map<int, CursesWindow*>& wins,
			  const int& shiftX);
void drawBoxes(const std::unordered_map<int, CursesWindow*>& wins);

#endif
