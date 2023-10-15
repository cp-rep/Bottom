/*
  File:
   taskInfo.hpp
  
  Description:
   The TaskInfo class is used to store and calcualte running "task" values read from
   "/proc/" directory files.
*/
#ifndef TASKINFO_HPP
#define TASKINFO_HPP
#include <string>

class TaskInfo {
public:
  TaskInfo(const std::string taskLine = "",
	   const unsigned int& running = 0,
	   const unsigned int& unSleep = 0,
	   const unsigned int& inSleep = 0,
	   const unsigned int& sleeping = 0,
	   const unsigned int& stopped = 0,
	   const unsigned int& zombie = 0,
	   const unsigned int& idle = 0,
	   const unsigned int& total = 0)
  {
    m_taskLine = taskLine;
    m_running = running;
    m_unSleep = unSleep;
    m_inSleep = inSleep;
    m_sleeping = sleeping;
    m_stopped = stopped;
    m_zombie = zombie;
    m_idle = idle;
    m_total = total;
  }

  // member functions
  void defineTaskLine();
  
  // getters
  const std::string& getTaskLine() { return m_taskLine; }
  const unsigned int& getRunning() { return m_running; }
  const unsigned int& getUnSleep() { return m_unSleep; }
  const unsigned int& getInSleep() { return m_inSleep; }
  const unsigned int& getStopped() { return m_stopped; }
  const unsigned int& getZombie() { return m_zombie; }
  const unsigned int& getIdle() { return m_idle; }
  const unsigned int& getTotal() { return m_total; }
  
  // setters
  void setTaskLine(const std::string& taskLine) { m_taskLine = taskLine; }  
  void setRunning(const unsigned int& running) { m_running = running; }
  void setUnSleep(const unsigned int& unSleep) { m_unSleep = unSleep; }
  void setInSleep(const unsigned int& inSleep) { m_inSleep = inSleep; }
  void setSleeping(const unsigned int& sleeping) { m_sleeping = sleeping; }
  void setStopped(const unsigned int& stopped) { m_stopped = stopped; }
  void setZombie(const unsigned int& zombie) { m_zombie = zombie; }
  void setIdle(const unsigned int& idle) { m_idle = idle; }
  void setTotal(const unsigned int& total) { m_total = total; }
  
private:
  std::string m_taskLine;
  unsigned int m_running;
  unsigned int m_unSleep;
  unsigned int m_inSleep;
  unsigned int m_sleeping;
  unsigned int m_stopped;
  unsigned int m_zombie;
  unsigned int m_idle;
  unsigned int m_total;
};

#endif
