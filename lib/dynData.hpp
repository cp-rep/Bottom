#ifndef DYNDATA_HPP
#define DYNDATA_HPP

struct DynamicTopWinData{
  std::string days;
  std::string hours;
  std::string minutes;
  std::string users;
  std::string outString;
  std::string timeType;
  std::string userString;
  std::string uptime;
  int uptimeDataCols;
  int loadAvgWinCols;
  int userCols;
  int userDataCols;
  int uptimePostCols;
  bool postWin;
  int nextWinStartX;
};

#endif
