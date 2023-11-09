/*
  File:
   changeProgramStates.hpp

   Description:
    Contains function declarations for functions that use user input to switch
    the current state of the Bottom program.
*/
#ifndef CHANGEPROGRAMSTATES_HPP
#define CHANGEPROGRAMSTATES_HPP
#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <unordered_map>
#include "_cursesWinConsts.hpp"
#include "_progStateConsts.hpp"
#include "cursesFunctions.hpp"
#include "cursesWindow.hpp"
#include "sortProcessLists.hpp"

void initializeProgramStates(std::unordered_map<char, int>& progStates);
void updateProgramState(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			std::unordered_map<int, CursesWindow*>& allWins,
			int& progState,			
			const int& prevState,
			int& sortState,			
			bool& quit,
			bool& highlight,
			const int& defaultKillPid,
			int& shiftY,
			int& shiftX,
			const int shiftDownMax);
void updateSortState(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
		     std::vector<int>& pids,
		     std::vector<int>& outPids,
		     const int& sortState);
void killState(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
	       std::unordered_map<int, CursesWindow*>& wins,
	       const int& defaultKillPid);
void helpState(std::unordered_map<int, CursesWindow*>& wins);
bool isValidKillSignal(const int& signal);
void cpuGraphState(std::unordered_map<int, CursesWindow*>& wins,
		   const std::unordered_map<int, ProcessInfo*>& procData);

#endif
