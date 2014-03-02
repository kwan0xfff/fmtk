// math_cart_baseline.cc -- reprsentative small test computations

#include <cmath>
#include <stdio.h>
#include <gtest/gtest.h>

#include "math/Cart3f.h"

using namespace cart3;

void print_cart3f(Cart3f& vec)
{
    printf("%4.2f %4.2f %4.2f\n", vec[0], vec[1], vec[2]);
}

void print_cart3f(const Cart3f& vec)
{
    Cart3f v = vec;
    print_cart3f(v);
}

const Cart3f vector_345 = Cart3f(3.0, 4.0, 5.0);
const Cart3f vector_100 = Cart3f(1.0, 0.0, 0.0);
const Cart3f vector_010 = Cart3f(0.0, 1.0, 0.0);
const Cart3f vector_001 = Cart3f(0.0, 0.0, 1.0);
const Cart3f vector_zero = Cart3f(0.0, 0.0, 0.0);

TEST(MathCartBaseline, First)
{
    Cart3f a = Cart3f(0.0, 1.0, 2.0);
    EXPECT_EQ(a[0], 0.0);
    print_cart3f(a);
}

TEST(MathCartBaseline, CompoundAsgnAdd)
{
    Cart3f sum =  vector_345;
    sum += vector_100;
    sum += vector_010;
    sum += vector_001;

    EXPECT_EQ(vector_345, Cart3f(3.0, 4.0, 5.0));
    EXPECT_EQ(sum, Cart3f(4.0, 5.0, 6.0));

    Cart3f diff = vector_345;
    diff -= vector_100;
    EXPECT_EQ(diff, Cart3f(2.0, 4.0, 5.0));
}

TEST(MathCartBaseline, CompoundAsgnMult)
{
    Cart3f result = vector_345;
    result *= 2.0;
    EXPECT_EQ(result, Cart3f(6.0, 8.0, 10.0));

    result /= 2.0;
    EXPECT_EQ(result, Cart3f(3.0, 4.0, 5.0));
}

TEST(MathCartBaseline, Index)
{
    enum { x=0, y=1, z=2 };
    Cart3f a = Cart3f(0.0, 1.0, 2.0);
    EXPECT_EQ(a[x], 0.0);
    EXPECT_EQ(a[y], 1.0);
    EXPECT_EQ(a[z], 2.0);

    float a2 = a[x];
    EXPECT_EQ(a2, 0.0);
    a[z] = a[x];
    EXPECT_EQ(a[2], 0.0);
    EXPECT_EQ(a, Cart3f(0.0, 1.0, 0.0));
}

TEST(MathCartBaseline, BinAdd)
{
    Cart3f result = vector_100 + vector_010;
    EXPECT_EQ(result, Cart3f(1.0, 1.0, 0.0));

    result = vector_100 - vector_010;
    EXPECT_EQ(result, Cart3f(1.0, -1.0, 0.0));
}

TEST(MathCartBaseline, BinMult)
{
    Cart3f result = vector_345 * 2.0;
    EXPECT_EQ(result, Cart3f(6.0, 8.0, 10.0));

    result = vector_345 / 2.0;
    EXPECT_EQ(result, Cart3f(1.5, 2.0, 2.5));
}

TEST(MathCartBaseline, BinMultSV)
{
    // friend: scalar * vector
    Cart3f result = 2.0 * vector_345;
    EXPECT_EQ(result, Cart3f(6.0, 8.0, 10.0));
}

TEST(MathCartBaseline, BinMultCross)
{
    Cart3f result = vector_100 ^ vector_010;
    EXPECT_EQ(result, vector_001);
}

TEST(MathCartBaseline, BinMultDot)
{
    float result = vector_100 * vector_010;
    EXPECT_EQ(result, 0.0);
}

TEST(MathCartBaseline, Unary)
{
    Cart3f result = -vector_345;
    EXPECT_EQ(result, Cart3f(-3.0, -4.0, -5.0));
}


