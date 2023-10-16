/*
  File: secondsToTime.hpp

  Description:
   Class definition for the SecondsToTime class.

   SecondsToTime creates objects with the ability to do conversions on time
   data such as converting hours to seconds, or minutes to seconds. It can
   also return formated time data for output.
*/
#ifndef SECONDSTOTIME_HPP
#define SECONDSTOTIME_HPP
#include <string>

#define MINUTE 60

class SecondsToTime{
public:
  // constructors
  SecondsToTime(const float seconds = 0);

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
  const float& getTotalSecs() const { return m_totalSecs; }
  
  // setters
  void setHours(const unsigned int& hours);
  void setMinutes(const unsigned int& minutes);
  void setSeconds(const unsigned int& seconds);
  void setTotalSecs(const float totalSecs) { m_totalSecs = totalSecs; }
  
private:
  // member variables
  unsigned int m_hours;
  unsigned int m_minutes;
  unsigned int m_seconds;
  float m_totalSecs;
};


#endif
