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
  m_running = running;
  m_unSleep = unSleep;
  m_inSleep = inSleep;
  m_sleeping = sleeping;
  m_stopped = stopped;
  m_zombie = zombie;
  m_idle = idle;
  m_total = total;
} // end of "TaskInfo Constructor"
