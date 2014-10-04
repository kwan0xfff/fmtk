// math_cart3d_baseline.cc -- reprsentative small test computations
// IEEE double precision

#include <cmath>
#include <stdio.h>
#include <gtest/gtest.h>

#include "math/Cart3d.h"

using namespace cart3;

void print_cart3d(Cart3d& vec)
{
    printf("%4.2f %4.2f %4.2f\n", vec[0], vec[1], vec[2]);
}

void print_cart3d(const Cart3d& vec)
{
    Cart3d v = vec;
    print_cart3d(v);
}

const Cart3d vector_345 = Cart3d(3.0, 4.0, 5.0);
const Cart3d vector_100 = Cart3d(1.0, 0.0, 0.0);
const Cart3d vector_010 = Cart3d(0.0, 1.0, 0.0);
const Cart3d vector_001 = Cart3d(0.0, 0.0, 1.0);
const Cart3d vector_zero = Cart3d(0.0, 0.0, 0.0);

TEST(MathCart3dBaseline, First)
{
    Cart3d a = Cart3d(0.0, 1.0, 2.0);
    EXPECT_EQ(a[0], 0.0);
    print_cart3d(a);
}

TEST(MathCart3dBaseline, CompoundAsgnAdd)
{
    Cart3d sum =  vector_345;
    sum += vector_100;
    sum += vector_010;
    sum += vector_001;

    EXPECT_EQ(vector_345, Cart3d(3.0, 4.0, 5.0));
    EXPECT_EQ(sum, Cart3d(4.0, 5.0, 6.0));

    Cart3d diff = vector_345;
    diff -= vector_100;
    EXPECT_EQ(diff, Cart3d(2.0, 4.0, 5.0));
}

TEST(MathCart3dBaseline, CompoundAsgnMult)
{
    Cart3d result = vector_345;
    result *= 2.0;
    EXPECT_EQ(result, Cart3d(6.0, 8.0, 10.0));

    result /= 2.0;
    EXPECT_EQ(result, Cart3d(3.0, 4.0, 5.0));
}

TEST(MathCart3dBaseline, Index)
{
    enum { x=0, y=1, z=2 };
    Cart3d a = Cart3d(0.0, 1.0, 2.0);
    EXPECT_EQ(a[x], 0.0);
    EXPECT_EQ(a[y], 1.0);
    EXPECT_EQ(a[z], 2.0);

    double a2 = a[x];
    EXPECT_EQ(a2, 0.0);
    a[z] = a[x];
    EXPECT_EQ(a[2], 0.0);
    EXPECT_EQ(a, Cart3d(0.0, 1.0, 0.0));
}

TEST(MathCart3dBaseline, BinAdd)
{
    Cart3d result = vector_100 + vector_010;
    EXPECT_EQ(result, Cart3d(1.0, 1.0, 0.0));

    result = vector_100 - vector_010;
    EXPECT_EQ(result, Cart3d(1.0, -1.0, 0.0));
}

TEST(MathCart3dBaseline, BinMult)
{
    Cart3d result = vector_345 * 2.0;
    EXPECT_EQ(result, Cart3d(6.0, 8.0, 10.0));

    result = vector_345 / 2.0;
    EXPECT_EQ(result, Cart3d(1.5, 2.0, 2.5));
}

TEST(MathCart3dBaseline, BinMultSV)
{
    // friend: scalar * vector
    Cart3d result = 2.0 * vector_345;
    EXPECT_EQ(result, Cart3d(6.0, 8.0, 10.0));
}

TEST(MathCart3dBaseline, BinMultCross)
{
    Cart3d result = vector_100 ^ vector_010;
    EXPECT_EQ(result, vector_001);
}

TEST(MathCart3dBaseline, BinMultDot)
{
    double result = vector_100 * vector_010;
    EXPECT_EQ(result, 0.0);
}

TEST(MathCart3dBaseline, Unary)
{
    Cart3d result = -vector_345;
    EXPECT_EQ(result, Cart3d(-3.0, -4.0, -5.0));
}


