// ============================================================================
// File: gtestCurseWindow.cpp
// Description:
//  Tests functionality of the CurseWindow class from the head and source file
//  curseWindow.hpp and curseWindow.cpp
// ============================================================================
#include <gtest/gtest.h>
#include "curseWindow.hpp"



/*
  Test the default constructor initializes correctly
 */
TEST(ClassTest, DefaultConstructor)
{
  CurseWindow win;
  EXPECT_EQ(0, win.getNumLines();
  EXPECT_EQ(0, win.getNumCols);
}
