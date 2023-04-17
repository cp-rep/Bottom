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
    gtests.cpp
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
