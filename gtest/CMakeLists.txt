#declare GoogleTest as a dependency to allow use of GoogleTest code
include(FetchContent)

# Get GoogleTest version to use with testing code
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG b796f7d44681514f58a683a3a71ff17c94edb0c1
)

# configure build of googletest
FetchContent_MakeAvailable(googletest)

# create executable that tests the code with attached source files
add_executable(
    unit_tests
    gtest_byteConverter.cpp
    gtest_COMMANDWindow.cpp
    gtest_cpuInfo.cpp
    gtest_cpuWindow.cpp
    gtest_extractFileData.cpp
    gtest_log.cpp
    gtest_mainWindow.cpp
    gtest_memInfo.cpp
    gtest_memWindow.cpp
    gtest_NIWindow.cpp
    gtest_percentCPUWindow.cpp
    gtest_percentMEMWindow.cpp
    gtest_PIDWindow.cpp
    gtest_processInfo.cpp
    gtest_PRWindow.cpp
    gtest_RESWindow.cpp
    gtest_secondsToTime.cpp
    gtest_SHRWindow.cpp
    gtest_sortProcessLists.cpp
    gtest_SWindow.cpp
    gtest_tasksWindow.cpp
    gtest_TIMEWindow.cpp
    gtest_topWindow.cpp
    gtest_USERWindow.cpp
    gtest_VIRTWindow.cpp
    gtest_taskInfo.cpp
    )

# link the test source files to application source files
target_link_libraries(unit_tests
  PRIVATE
    Gtest
    gtest_main
  )

# automatically discover the unit tests
include(GoogleTest)
gtest_discover_tests(unit_tests)
