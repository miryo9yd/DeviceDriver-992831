
#include "gtest/gtest.h"  // 비공식
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp" // 자체파일 순으로 


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}