/*
  File: secondsToTime.hpp
 */
#ifndef SECONDSTOTIME_HPP
#define SECONDSTOTIME_HPP

#define MINUTE 60

class SecondsToTime{
public:
  // constructors
  SecondsToTime(const unsigned int hours = 0,
		const unsigned int minutes = 0,
		const unsigned int seconds = 0) : m_hours(hours),
						  m_minutes(minutes),
						  m_seconds(seconds){}

  // member functions
  const int convertToHours(const int& secs) const { return secs/(MINUTE * MINUTE); }
  const int convertToMinutes(const int& secs) const { return (secs/MINUTE) % MINUTE; }
  const int findRemainingSeconds(const int& secs) const { return secs % MINUTE; }
  
  // getters
  const unsigned int& getHours() const { return m_hours; }
  const unsigned int& getMinutes() const { return m_minutes; }
  const unsigned int& getSeconds() const { return m_seconds; }
  
  // setters
  void setHours(const unsigned int& hours) { m_hours = hours; }
  void setMinutes(const unsigned int& minutes) { m_minutes = minutes; }
  void setSeconds(const unsigned int& seconds) { m_seconds = seconds; }
  
private:
  // member variables
  unsigned int m_hours;
  unsigned int m_minutes;
  unsigned int m_seconds;
};


#endif
