/*
  File:
   taskInfo.hpp
  
  Description:
   The class definition for the TaskInfo class.

   The TaskInfo class is used to store and calcualte process state values.
*/
#ifndef TASKINFO_HPP
#define TASKINFO_HPP
#include <string>

class TaskInfo {
public:
  TaskInfo(const unsigned int& running = 0,
	   const unsigned int& unSleep = 0,
	   const unsigned int& inSleep = 0,
	   const unsigned int& sleeping = 0,
	   const unsigned int& stopped = 0,
	   const unsigned int& zombie = 0,
	   const unsigned int& idle = 0,
	   const unsigned int& total = 0);

  // member functions
  const unsigned int calcSleeping() const;
  const unsigned int calcTotal() const;

  // getters
  const unsigned int& getRunning() const { return m_running; }
  const unsigned int& getUnSleep() const { return m_unSleep; }
  const unsigned int& getInSleep() const { return m_inSleep; }
  const unsigned int& getStopped() const { return m_stopped; }
  const unsigned int& getSleeping() const { return m_sleeping; }
  const unsigned int& getZombie() const { return m_zombie; }
  const unsigned int& getIdle() const { return m_idle; }
  const unsigned int& getTotal() const { return m_total; }
  
  // setters
  void setRunning(const unsigned int& running) { m_running = running; }
  void setUnSleep(const unsigned int& unSleep) { m_unSleep = unSleep; }
  void setInSleep(const unsigned int& inSleep) { m_inSleep = inSleep; }
  void setSleeping(const unsigned int& sleeping) { m_sleeping = sleeping; }
  void setStopped(const unsigned int& stopped) { m_stopped = stopped; }
  void setZombie(const unsigned int& zombie) { m_zombie = zombie; }
  void setIdle(const unsigned int& idle) { m_idle = idle; }
  void setTotal(const unsigned int& total) { m_total = total; }
  
private:
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
