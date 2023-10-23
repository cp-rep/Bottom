/*
  _cursesWinConsts.hpp
 */
#ifndef _CURSESWINCONSTS_HPP
#define _CURSESWINCONSTS_HPP

// window index constants
enum _WINS {
  _MAINWIN,
  _TOPWIN, 
  _TASKSWIN,
  _CPUWIN,
  _MEMWIN,
  _PIDWIN,
  _USERWIN,
  _PRWIN,
  _NIWIN,
  _VIRTWIN,
  _RESWIN,
  _SHRWIN,
  _SWIN,
  _PROCCPUWIN,
  _PROCMEMWIN,
  _PROCTIMEWIN,
  _COMMANDWIN,
  _TASKSTOTAL,
  _TASKSRUNNING,
  _TASKSSLEEPING,
  _TASKSSTOPPED,
  _TASKSZOMBIE // 21
};

// window count constants
#define _BOTTOMWINTOTAL 12
#define _YOFFSET 6

#endif
