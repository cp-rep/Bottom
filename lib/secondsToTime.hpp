/*
  File: secondsToTime.hpp
 */
#ifndef SECONDSTOTIME_HPP
#define SECONDSTOTIME_HPP
#include <string>

#define MINUTE 60

class SecondsToTime{
public:
  // constructors
  SecondsToTime(const unsigned int hours = 0,
		const unsigned int minutes = 0,
		const unsigned int seconds = 0);

  // member functions
  const int convertToHours(const int& secs) const;
  const int convertToMinutes(const int& secs) const;
  const int findRemainingSeconds(const int& secs) const;
  std::string returnHHMMSS(const int& hours,
			   const int& minutes,
			   const int& seconds) const;
  
  // getters
  const unsigned int& getHours() const;
  const unsigned int& getMinutes() const;
  const unsigned int& getSeconds() const; 
  
  // setters
  void setHours(const unsigned int& hours);
  void setMinutes(const unsigned int& minutes);
  void setSeconds(const unsigned int& seconds);
  
private:
  // member variables
  unsigned int m_hours;
  unsigned int m_minutes;
  unsigned int m_seconds;
};


#endif
