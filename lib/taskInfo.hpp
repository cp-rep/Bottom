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
  const unsigned int& getRunning() const;
  const unsigned int& getUnSleep() const;
  const unsigned int& getInSleep() const;
  const unsigned int& getStopped() const;
  const unsigned int& getSleeping() const;
  const unsigned int& getZombie() const;
  const unsigned int& getIdle() const;
  const unsigned int& getTotal() const;
  
  // setters
  void setRunning(const unsigned int& running);
  void setUnSleep(const unsigned int& unSleep);
  void setInSleep(const unsigned int& inSleep);
  void setSleeping(const unsigned int& sleeping);
  void setStopped(const unsigned int& stopped);
  void setZombie(const unsigned int& zombie);
  void setIdle(const unsigned int& idle);
  void setTotal(const unsigned int& total);
  
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
