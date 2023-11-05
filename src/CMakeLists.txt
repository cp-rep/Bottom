# add the librarys we're going to test
add_library(Gtest)

# direct the file names for the libaries
target_sources(Gtest
  PRIVATE
  # program source files
  byteConverter.cpp
  cpuInfo.cpp  
  extractFileData.cpp
  memInfo.cpp
  processInfo.cpp
  secondsToTime.cpp
  taskInfo.cpp
  sortProcessLists.cpp
  
  PUBLIC
  # program library files
  ../lib/byteConverter.hpp  
  ../lib/cpuInfo.hpp  
  ../lib/extractFileData.hpp
  ../lib/memInfo.hpp
  ../lib/processInfo.hpp
  ../lib/secondsToTime.hpp
  ../lib/taskInfo.hpp
  ../lib/sortProcessLists.hpp
  )

# direct the location of the files
target_include_directories(Gtest
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_CURRENT_LIST_DIR}/../lib    
  )
