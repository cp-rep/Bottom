// ============================================================================
// File: gtestsCurseWindow.cpp
// Description:
//  Tests functionality of the CurseWindow class from the head and source file
//  curseWindow.hpp and curseWindow.cpp
// ============================================================================
#include <gtest/gtest.h>
#include "curseWindow.hpp"

TEST(ClassTest, DefaultConstructor)
{
  CurseWindow win;
  EXPECT_EQ(0, win.getNumCols());
}
