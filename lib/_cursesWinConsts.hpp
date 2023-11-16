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
  _MAINWIN,
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
  _TASKSTOTALDATAWIN,
  _TASKSRUNDATAWIN,
  _TASKSSLEEPDATAWIN,
  _TASKSSTOPDATAWIN,
  _TASKSZOMBDATAWIN,
  _CPUUSDATAWIN,
  _CPUSYDATAWIN,
  _CPUNIDATAWIN,
  _CPUIDDATAWIN,
  _CPUWADATAWIN,
  _CPUHIDATAWIN,
  _CPUSIDATAWIN,
  _CPUSTDATAWIN,
  _MAINMEMTOTALDATAWIN,
  _MAINMEMFREEDATAWIN,
  _MAINMEMUSEDDATAWIN,
  _MAINMEMBUFFCACHEDATAWIN,
  _SWAPMEMTOTALDATAWIN,
  _SWAPMEMFREEDATAWIN,
  _SWAPMEMUSEDDATAWIN,
  _MEMAVAILDATAWIN,
  
  _TASKSTOTALWIN,
  _TASKSRUNWIN,
  _TASKSSLEEPWIN,
  _TASKSSTOPWIN,
  _TASKSZOMBWIN,
  _CPUUSWIN,
  _CPUSYWIN,
  _CPUNIWIN,
  _CPUIDWIN,
  _CPUWAWIN,
  _CPUHIWIN,
  _CPUSIWIN,
  _CPUSTWIN,
  _MIBTOTALWIN,
  _MIBFREEWIN,
  _MIBUSEDWIN,
  _MIBBUFFCACHEWIN,
  _MIBSWAPTOTALWIN,
  _MIBSWAPFREEWIN,
  _MIBSWAPUSEDWIN,
  _MIBMEMAVAILWIN,  
  
  _CPUGRAPHWIN,
  _MEMGRAPHWIN,
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

// universal label consts
#define _TOTALLABELCOLS 6

// tasks window label consts
#define _TASKSROWSTARTY 1
#define _TASKSROWNAMECOLS 6
#define _TASKSRUNLABELCOLS 8
#define _TASKSSLEEPLABELCOLS 9
#define _TASKSSTOPLABELCOLS 8
#define _TASKSZOMBLABELCOLS 6
#define _TASKSROWNAMESTARTX 0
#define _TASKSRUNLABELSTARTX 19
#define _TASKSSLEEPLABELSTARTX 31
#define _TASKSSTOPLABELSTARTX 46
#define _TASKSZOMBLABELSTARTX 59

// tasks data window consts
#define _TASKSDATAWINCOLS 4
#define _TASKSDATASTARTY 1
#define _TASKSTOTALDATASTARTX 6
#define _TASKSRUNDATASTARTX 17
#define _TASKSSLEEPDATASTARTX 30
#define _TASKSSTOPDATASTARTX 44
#define _TASKSZOMBDATASTARTX 57

// CPU data window consts
#define _CPUDATAWINCOLS 5
#define _CPUDATASTARTY 2
#define _CPUUSDATASTARTX 8
#define _CPUSYDATASTARTX 17
#define _CPUNIDATASTARTX 26
#define _CPUIDDATASTARTX 35
#define _CPUWADATASTARTX 44
#define _CPUHIDATASTARTX 53
#define _CPUSIDATASTARTX 62
#define _CPUSTDATASTARTX 71

// main/swap mem data window consts
#define _MEMDATAWINCOLS 9
#define _MAINMEMSTARTY 3
#define _MAINMEMTOTALDATASTARTX 9
#define _MAINMEMFREEDATASTARTX 25
#define _MAINMEMUSEDDATASTARTX 40
#define _MAINMEMBUFFCACHEDATASTARTX 55
#define _SWAPMEMSTARTY 4
#define _SWAPMEMTOTALDATASTARTX 9
#define _SWAPMEMFREEDATASTARTX 25
#define _SWAPMEMUSEDDATASTARTX 40
#define _MEMAVAILDATASTARTX 55

#endif
