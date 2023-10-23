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
void updateStateValues(std::unordered_map<int, CursesWindow*>& allWins,
		       std::unordered_map<char, int>& progStates,
		       const int& userInput,
		       int& sortState,
		       int& prevState,
		       int& progState,
		       const bool& highlight,
		       int& highlightIndex);
void changeProgramState(int& progState,
			const int& prevState,
			bool& quit,
			bool& highlight);
void bottomWinsProcSortState(std::unordered_map<int, ProcessInfo*>& allProcessInfo,
			    std::vector<int>& pids,
			    std::vector<int>& outPids,
			    const int& userInput);
void bottomWinsShiftState(std::unordered_map<int, CursesWindow*>& allWins,
			  const int& shiftState,
			  int& shiftY,
			  int& shiftX,
			  const int shiftDownMax);
void changeProgramState(const std::unordered_map<int, CursesWindow*>& allWins,
			int& progState,
			const int& prevState,
			bool& quit,
			bool& highlight);

void killState(const std::unordered_map<int, CursesWindow*>& allWins);
#endif
