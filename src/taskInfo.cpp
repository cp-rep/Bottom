/*
  File: 
   taskInfo.hpp
 
  Description:
   The class implementation for the TaskInfo class.
*/
#include "taskInfo.hpp"



/*
  Function:
   TaskInfo Constructor
   
  Description:
   The class constructor for creating TaskInfo objects and 
   initializing related class data.

  Input:
   running              - A reference to a const unsigned int
                          value that represents the state "R"
			  for a current running process.

   unSleep              - A reference to a const unsigned int
                          value that represents the
			  uninteruptible sleep state "D" of a
			  process.

   inSleep              - A reference to a const unsigned int
                          value that represents the
			  interuptible sleep state "S" of a
			  process.

   sleeping             - A reference to a const unsigned int
                          value that represents the total amount
			  of sleeping processes.


   stopped              - A reference to a const unsigned int
                          value that represents the
			  stopped/traced state "T" of a process.

   zombie               - A reference to a const unsigned int
                          value that represents the
			  zombie state "Z" of a process.
			  
   idle                 - A reference to a const unsigned int
                          value that represents the
			  idle state "I" of a process.

   total                - A reference to a const unsigned int
                          value that represents the total amount
			  of allocated process in the process list.
			  
  Output:
   NONE
*/
TaskInfo::TaskInfo(const unsigned int& running,
		   const unsigned int& unSleep,
		   const unsigned int& inSleep,
		   const unsigned int& sleeping,
		   const unsigned int& stopped,
		   const unsigned int& zombie,
		   const unsigned int& idle,
		   const unsigned int& total)
{
  setRunning(running);
  setUnSleep(unSleep);
  setInSleep(inSleep);
  setSleeping(sleeping);
  setStopped(stopped);
  setZombie(zombie);
  setIdle(idle);
  setTotal(total);
} // end of "TaskInfo Constructor"



/*
  Function:

  Description:

  Input:

  Output:
*/
const unsigned int TaskInfo::calcSleeping() const
{
  return getInSleep() + getUnSleep() + getIdle();
} // end of "calcSleeping"



/*
  Function:

  Description:

  Input:

  Output:
*/
const unsigned int TaskInfo::calcTotal() const
{
  return getRunning() + getSleeping();
} // end of "calcTotal"



/*
  Function:

  Description:

  Input:

  Output:
*/
const unsigned int& TaskInfo::getRunning() const
{
  return m_running;
} // end of "getRunning"



/*
  Function:

  Description:

  Input:

  Output:
*/
const unsigned int& TaskInfo::getUnSleep() const
{
  return m_unSleep;
} // end of "getUnSleep"



/*
  Function:

  Description:

  Input:

  Output:
*/
const unsigned int& TaskInfo::getInSleep() const
{
  return m_inSleep;
} // end of "getInSleep"



/*
  Function:
   getSleeping

  Description:

  Input:

  Output:
*/
const unsigned int& TaskInfo::getSleeping() const
{
  return m_sleeping;
} // end of "getSleeping"



/*
  Function:

  Description:

  Input:

  Output:
*/
const unsigned int& TaskInfo::getStopped() const
{
  return m_stopped;
} // end of "getStopped"



/*
  Function:

  Description:

  Input:

  Output:
*/
const unsigned int& TaskInfo::getZombie() const
{
  return m_zombie;
} // end of "getZombie"



/*
  Function:

  Description:

  Input:

  Output:
*/
const unsigned int& TaskInfo::getIdle() const
{
  return m_idle;
} // end of "getIdle"



/*
  Function:

  Description:

  Input:

  Output:
*/
const unsigned int& TaskInfo::getTotal() const
{
  return m_total;
} // end of "getTotal"
  


/*
  Function:

  Description:

  Input:

  Output:
*/
void TaskInfo::setRunning(const unsigned int& running)
{
  m_running = running;
} // end of "setRunning"



/*
  Function:

  Description:

  Input:

  Output:
*/
void TaskInfo::setUnSleep(const unsigned int& unSleep)
{
  m_unSleep = unSleep;
} // end of "setUnSleep"



/*
  Function:

  Description:

  Input:

  Output:
*/
void TaskInfo::setInSleep(const unsigned int& inSleep)
{
  m_inSleep = inSleep;
} // end of "setInSleep"



/*
  Function:

  Description:

  Input:

  Output:
*/
void TaskInfo::setSleeping(const unsigned int& sleeping)
{
  m_sleeping = sleeping;
} // end of "setSleeping"



/*
  Function:

  Description:

  Input:

  Output:
*/
void TaskInfo::setStopped(const unsigned int& stopped)
{
  m_stopped = stopped;
} // end of "setStopped"



/*
  Function:

  Description:

  Input:

  Output:
*/
void TaskInfo::setZombie(const unsigned int& zombie)
{
  m_zombie = zombie;
} // end of "setZombie"



/*
  Function:

  Description:

  Input:

  Output:
*/
void TaskInfo::setIdle(const unsigned int& idle)
{
  m_idle = idle;
} // end of "setIdle"



/*
  Function:

  Description:

  Input:

  Output:
*/
void TaskInfo::setTotal(const unsigned int& total)
{
  m_total = total;
} // end of "setTotal"
