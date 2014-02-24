// math_cart_baseline.cc -- reprsentative small test computations

#include <cmath>
#include <stdio.h>
#include <gtest/gtest.h>

#include "math/Cart3f.h"

using namespace cart3;

#if 0
void print_cart3f(Cart3f& vec)
{
    printf("%4.2f %4.2f %4.2f\n", vec[0], vec[1], vec[2]);
}

void print_cart3f(const Cart3f& vec)
{
    Cart3f v = vec;
    print_cart3f(v);
}
#endif // 0

const Cart3f vector_100 = Cart3f(1.0, 0.0, 0.0);
const Cart3f vector_010 = Cart3f(0.0, 1.0, 0.0);
const Cart3f vector_zero = Cart3f(0.0, 0.0, 0.0);

const Mat33f matrix_zero = Mat33f(
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0);

const Mat33f matrix_ones = Mat33f(
    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0);

const Mat33f matrix_ident = Mat33f(
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0);

const Mat33f matrix_twist = Mat33f(
    0.0, 1.0, 2.0,
    1.0, 1.0, 1.0,
    2.0, 1.0, 0.0);

TEST(MathCartMat33Baseline, First)
{
    Mat33f a = matrix_ident;
    EXPECT_EQ(a, matrix_ident);  // deceptively simple, lots happening
}

TEST(MathCartMat33Baseline, Construct)
{
    // construct from scalars
    Mat33f a = Mat33f(
        0.0, 1.0, 2.0,
        3.0, 4.0, 5.0,
        6.0, 7.0, 8.0);
    EXPECT_EQ(a[0][0], 0.0);
    EXPECT_EQ(a[0][2], 2.0);
    EXPECT_EQ(a[2][1], 7.0);

    // construct from vectors
    Mat33f b = Mat33f(vector_100, vector_010, vector_zero);
    EXPECT_EQ(b, Mat33f(
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 0.0));
    EXPECT_NE(b, matrix_zero);
}

TEST(MathCartMat33Baseline, CompoundAsgnAdd)
{
    Mat33f sum =  matrix_zero;
    sum += matrix_ident;
    sum += matrix_ones;

    EXPECT_EQ(matrix_zero, Mat33f(
            0.0, 0.0, 0.0,
            0.0, 0.0, 0.0,
            0.0, 0.0, 0.0 ));
    EXPECT_EQ(sum, Mat33f(
            2.0, 1.0, 1.0,
            1.0, 2.0, 1.0,
            1.0, 1.0, 2.0 ));

    Mat33f diff = matrix_ones;
    diff -= matrix_ident;
    EXPECT_EQ(diff, Mat33f(
            0.0, 1.0, 1.0,
            1.0, 0.0, 1.0,
            1.0, 1.0, 0.0 ));
}


TEST(MathCartMat33Baseline, CompoundAsgnMult)
{
    Mat33f sum =  matrix_zero;
    Mat33f result = matrix_twist;
    result *= 2.0;
    EXPECT_EQ(result, Mat33f(
            0.0, 2.0, 4.0,
            2.0, 2.0, 2.0,
            4.0, 2.0, 0.0 ));
    result /= 2.0;
    EXPECT_EQ(result, Mat33f(
            0.0, 1.0, 2.0,
            1.0, 1.0, 1.0,
            2.0, 1.0, 0.0 ));
}


TEST(MathCartMat33Baseline, Index)
{
    enum { x=0, y=1, z=2 };
    Mat33f a = Mat33f(
        0.0, 1.0, 2.0,
        3.0, 4.0, 5.0,
        6.0, 7.0, 8.0);
    EXPECT_EQ(a[x][x], 0.0);
    EXPECT_EQ(a[x][z], 2.0);
    EXPECT_EQ(a[y][x], 3.0);
    EXPECT_EQ(a[z][y], 7.0);

    float axz = a[x][z];
    a[z][x] = a[x][z];
    EXPECT_EQ(axz, 2.0);
    EXPECT_EQ(a[z], Cart3f(2.0, 7.0, 8.0));
}

TEST(MathCartMat33Baseline, BinAdd)
{
    Mat33f result = matrix_ones + matrix_ident;
    EXPECT_EQ(result, Mat33f(
            2.0, 1.0, 1.0,
            1.0, 2.0, 1.0,
            1.0, 1.0, 2.0 ));

    result = matrix_ones - matrix_ident;
    EXPECT_EQ(result, Mat33f(
            0.0, 1.0, 1.0,
            1.0, 0.0, 1.0,
            1.0, 1.0, 0.0 ));
}

TEST(MathCartMat33Baseline, BinMult)
{
    Mat33f result = matrix_twist * 2.0;
    EXPECT_EQ(result, Mat33f(
            0.0, 2.0, 4.0,
            2.0, 2.0, 2.0,
            4.0, 2.0, 0.0 ));

    result = matrix_twist / 2.0;
    EXPECT_EQ(result, Mat33f(
            0.0, 0.5, 1.0,
            0.5, 0.5, 0.5,
            1.0, 0.5, 0.0 ));
}


TEST(MathCartMat33Baseline, BinMultDot)
{
    Mat33f rot30cclock = Mat33f(
        // rotate 30 degrees (pi/6) counterclockwise
         0.500, -0.866, 0.0,
         0.866,  0.500, 0.0,
         0.0,    0.0,   1.0);
    Cart3f xseg = Cart3f(1.0, 0.0, 0.0);
    //print_cart3f(xseg);

    // v = m * v
    Cart3f vresult = rot30cclock * xseg;
    //print_cart3f(vresult);
    EXPECT_EQ(vresult, Cart3f(0.5, 0.866, 0.0));

    // m = m * m
    Mat33f mresult = rot30cclock * matrix_ident;
    //print_cart3f(mresult[0]);
    //print_cart3f(mresult[1]);
    //print_cart3f(mresult[2]);
    EXPECT_EQ(mresult, rot30cclock);
}

TEST(MathCartMat33Baseline, Unary)
{
    Mat33f result = -matrix_twist;
    EXPECT_EQ(result, Mat33f(
         0.0, -1.0, -2.0,
        -1.0, -1.0, -1.0,
        -2.0, -1.0, -0.0));
}

