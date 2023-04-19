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
  EXPECT_EQ(nullptr, win.getWindow());
  EXPECT_EQ(0, win.getNumLines());
  EXPECT_EQ(0, win.getNumCols());
  EXPECT_EQ(0, win.getMaxWindowY());
  EXPECT_EQ(0, win.getMaxWindowX());
  EXPECT_EQ(0, win.getMinWindowY());    
  EXPECT_EQ(0, win.getMinWindowX());
  EXPECT_EQ(0, win.getCenterY());
  EXPECT_EQ(0, win.getCenterX());
  EXPECT_EQ(0, win.getStartY());
  EXPECT_EQ(0, win.getStartX());
  EXPECT_EQ(0, win.getCurrentY());
  EXPECT_EQ(0, win.getCurrentX());
  EXPECT_EQ(0, win.getPreviousY());
  EXPECT_EQ(0, win.getPreviousX());    
}
