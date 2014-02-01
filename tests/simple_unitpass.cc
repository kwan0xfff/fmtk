// simple_unitpass.cc -- simplistic test

#include <gtest/gtest.h>

int Abs(int n) {
    int result ;
    result = (n < 0) ? -n : n;
    return result;
}


TEST(AbsTest, HandleZero) {
    EXPECT_EQ(0, Abs(0));
}

TEST(AbsTest, HandleNeg) {
    EXPECT_EQ(1, Abs(-1));
    EXPECT_EQ(100, Abs(-100));
}

TEST(AbsTest, HandlePos) {
    EXPECT_EQ(1, Abs(1));
    EXPECT_EQ(100, Abs(100));
}


