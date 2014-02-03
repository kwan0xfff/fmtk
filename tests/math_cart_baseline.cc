// math_cart_baseline.cc -- reprsentative small test computations

#include <cmath>
#include <stdio.h>
#include <gtest/gtest.h>

#include "math/Cart3f.h"

using namespace cart3;

TEST(MathCartBaseline, First)
{
    Cart3f a = Cart3f(0.0, 1.0, 2.0);
    EXPECT_EQ(a[0], 0.0);
}

TEST(MathCartBaseline, IndexSubscript)
{
    enum { x=0, y=1, z=2 };
    Cart3f a = Cart3f(0.0, 1.0, 2.0);
    EXPECT_EQ(a[x], 0.0);
    EXPECT_EQ(a[y], 1.0);
    EXPECT_EQ(a[z], 2.0);
}


