/*
  _cursesWinConsts.hpp
 */
#ifndef _CURSESWINCONSTS_HPP
#define _CURSESWINCONSTS_HPP

// color pair values
enum CursesColors {
  none,
  _WHITE_TEXT,
  _BLACK_TEXT
} ;

// window index constants
enum _WINS {
  // stdscr
  _MAINWIN,

  // process windows
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

  // top win
  _TOPWIN,
  _TOPCURRTIMEWIN,
  _TOPUPWIN,
  _TOPUPDATAWIN,
  _TOPUPPOSTWIN,
  _TOPUSERDATAWIN,
  _TOPUSERWIN,
  _TOPLOADAVGWIN,
  _TOPLOADAVGDATAWIN,
  
  // tasks windows
  _TASKSWIN,
  _TASKSROWNAMEWIN,
  _TASKSTOTALWIN,
  _TASKSRUNWIN,
  _TASKSSLEEPWIN,
  _TASKSSTOPWIN,
  _TASKSZOMBWIN,

  // CPU(s) windows
  _CPUWIN,
  _CPUUSWIN,
  _CPUSYWIN,
  _CPUNIWIN,
  _CPUIDWIN,
  _CPUWAWIN,
  _CPUHIWIN,
  _CPUSIWIN,
  _CPUSTWIN,

  // MIB MEM windows
  _MEMWIN,
  _MEMTOTALWIN,
  _MEMFREEWIN,
  _MEMUSEDWIN,
  _MEMBUFFCACHEWIN,

  //MIB SWAP WINDOWS
  _SWAPWIN,
  _SWAPTOTALWIN,
  _SWAPFREEWIN,
  _SWAPUSEDWIN,
  _MEMAVAILWIN,

  // tasks data windows
  _TASKSTOTALDATAWIN,
  _TASKSRUNDATAWIN,
  _TASKSSLEEPDATAWIN,
  _TASKSSTOPDATAWIN,
  _TASKSZOMBDATAWIN,

  // CPU(s) data windows
  _CPUUSDATAWIN,
  _CPUSYDATAWIN,
  _CPUNIDATAWIN,
  _CPUIDDATAWIN,
  _CPUWADATAWIN,
  _CPUHIDATAWIN,
  _CPUSIDATAWIN,
  _CPUSTDATAWIN,

  // MiB Mem data windows
  _MEMTOTALDATAWIN,
  _MEMFREEDATAWIN,
  _MEMUSEDDATAWIN,
  _MEMBUFFCACHEDATAWIN,

  // MiB Swap data windows
  _SWAPTOTALDATAWIN,
  _SWAPFREEDATAWIN,
  _SWAPUSEDDATAWIN,
  _MEMAVAILDATAWIN,

  // graphs
  _CPUGRAPHWIN,
  _MEMGRAPHWIN,

  // other
  _USERINPUTWIN,
  _HELPWIN
};

// window position constants
#define _YOFFSET 6

// process window size consts
#define _PIDWINCOLS 7
#define _USERWINCOLS 8
#define _PRWINCOLS 3
#define _NIWINCOLS 3
#define _VIRTWINCOLS 7
#define _RESWINCOLS 6
#define _SHRWINCOLS 6
#define _SWINCOLS 1
#define _PROCCPUWINCOLS 5
#define _PROCMEMWINCOLS 5
#define _PROCTIMEWINCOLS 9
#define _COMMANDWINCOLS 40

// top window consts
#define _TOPWINSTARTY 0
#define _TOPWINCOLS 5
#define _TOPCURRTIMEWINCOLS 8
#define _TOPUPWINCOLS 2
#define _TOPUSERWINCOLS 5
#define _TOPLOADAVGWINCOLS 13

// tasks window consts
#define _TASKSWINSTARTY 1
#define _TASKSWINCOLS 6
#define _TASKSWINSTARTX 0
#define _TASKSTOTALWINCOLS 6
#define _TASKSTOTALWINSTARTX 11
#define _TASKSRUNWINCOLS 8
#define _TASKSRUNWINSTARTX 22
#define _TASKSSLEEPWINCOLS 9
#define _TASKSSLEEPWINSTARTX 35
#define _TASKSSTOPWINCOLS 8
#define _TASKSSTOPWINSTARTX 49
#define _TASKSZOMBWINCOLS 6
#define _TASKSZOMBWINSTARTX 62

// tasks data window consts
#define _TASKSDATAWINCOLS 4
#define _TASKSDATAWINSTARTY 1
#define _TASKSTOTALDATAWINSTARTX 6
#define _TASKSRUNDATAWINSTARTX 17
#define _TASKSSLEEPDATAWINSTARTX 30
#define _TASKSSTOPDATAWINSTARTX 44
#define _TASKSZOMBDATAWINSTARTX 57

// CPU win consts
#define _CPUWINSTARTY 2
#define _CPUWINCOLS 8
#define _CPUWINSTARTX 0
#define _CPUUSWINCOLS 3
#define _CPUUSWINSTARTX 14
#define _CPUSYWINCOLS 3
#define _CPUSYWINSTARTX 23
#define _CPUNIWINCOLS 3
#define _CPUNIWINSTARTX 32
#define _CPUIDWINCOLS 3
#define _CPUIDWINSTARTX 41
#define _CPUWAWINCOLS 3
#define _CPUWAWINSTARTX 50
#define _CPUHIWINCOLS 3
#define _CPUHIWINSTARTX 59
#define _CPUSIWINCOLS 3
#define _CPUSIWINSTARTX 68
#define _CPUSTWINCOLS 2
#define _CPUSTWINSTARTX 77

// CPU data window consts
#define _CPUDATAWINCOLS 5
#define _CPUDATAWINSTARTY 2
#define _CPUUSDATAWINSTARTX 8
#define _CPUSYDATAWINSTARTX 17
#define _CPUNIDATAWINSTARTX 26
#define _CPUIDDATAWINSTARTX 35
#define _CPUWADATAWINSTARTX 44
#define _CPUHIDATAWINSTARTX 53
#define _CPUSIDATAWINSTARTX 62
#define _CPUSTDATAWINSTARTX 71

// mem window consts
#define _MEMWINSTARTY 3
#define _MEMWINCOLS 9
#define _MEMWINSTARTX 0
#define _MEMTOTALWINCOLS 6
#define _MEMTOTALWINSTARTX 19
#define _MEMFREEWINCOLS 5
#define _MEMFREEWINSTARTX 35
#define _MEMUSEDWINCOLS 5
#define _MEMUSEDWINSTARTX 50
#define _MEMBUFFCACHEWINCOLS 10
#define _MEMBUFFCACHEWINSTARTX 65

// swap window consts
#define _SWAPWINSTARTY 4
#define _SWAPWINCOLS 9
#define _SWAPWINSTARTX 0
#define _SWAPTOTALWINCOLS 6
#define _SWAPTOTALWINSTARTX 19
#define _SWAPFREEWINCOLS 5
#define _SWAPFREEWINSTARTX 35
#define _SWAPUSEDWINCOLS 5
#define _SWAPUSEDWINSTARTX 50
#define _MEMAVAILWINCOLS 9
#define _MEMAVAILWINSTARTX 65

// mem data window consts
#define _MEMDATAWINCOLS 9
#define _MEMWINSTARTY 3
#define _MEMTOTALDATAWINSTARTX 9
#define _MEMFREEDATAWINSTARTX 25
#define _MEMUSEDDATAWINSTARTX 40
#define _MEMBUFFCACHEDATAWINSTARTX 55

// swap data window consts
#define _SWAPWINSTARTY 4
#define _SWAPTOTALDATAWINSTARTX 9
#define _SWAPFREEDATAWINSTARTX 25
#define _SWAPUSEDDATAWINSTARTX 40
#define _MEMAVAILDATAWINSTARTX 55

#endif
