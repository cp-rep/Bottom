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
#include <mutex>

#define MINUTE 60

class SecondsToTime{
public:
  // constructors
  SecondsToTime(const float& seconds = 0);

  // member functions
  const unsigned int convertToHours(const unsigned int& seconds) const;
  const unsigned int convertToMinutes(const unsigned int& seconds) const;
  const unsigned int findRemainingSeconds(const unsigned int& seconds) const;
  std::string returnHHMMSS(const unsigned int& hours,
			   const unsigned int& minutes,
			   const unsigned int& seconds) const;
  
  // getters
  const unsigned int& getHours() const { return m_hours; }
  const unsigned int& getMinutes() const { return m_minutes; }
  const unsigned int& getSeconds() const { return m_seconds; }
  const float& getTotalSeconds() const { return m_totalSeconds; }
  
  // setters
  void setHours(const unsigned int& hours) {
    std::lock_guard<std::mutex> lock(m_hoursMut);
    m_hours = hours; }
  void setMinutes(const unsigned int& minutes) {
    std::lock_guard<std::mutex> lock(m_minutesMut);
    m_minutes = minutes; }
  void setSeconds(const unsigned int& seconds) {
    std::lock_guard<std::mutex> lock(m_secondsMut);
    m_seconds = seconds; }
  void setTotalSeconds(const float& totalSeconds) {
    std::lock_guard<std::mutex> lock(m_totalSecondsMut);
    m_totalSeconds = totalSeconds; }
  
private:
  // member variables
  unsigned int m_hours;
  unsigned int m_minutes;
  unsigned int m_seconds;
  float m_totalSeconds;

  mutable std::mutex m_hoursMut;
  mutable std::mutex m_minutesMut;
  mutable std::mutex m_secondsMut;
  mutable std::mutex m_totalSecondsMut;
};

#endif
