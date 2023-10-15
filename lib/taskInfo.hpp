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
  TaskInfo(const std::string taskLine = "") { m_taskLine = taskLine; };

  // member functions

  // getters
  const std::string getTaskLine() { return m_taskLine; }
  
  // setters
  void setTaskLine(const std::string& taskLine) { m_taskLine = taskLine; }
  
private:
  std::string m_taskLine;
};

#endif
