// math_cart_baseline.cc -- reprsentative small test computations

#include <cmath>
#include <stdio.h>
#include <gtest/gtest.h>

#include "math/interpbilinear.h"

TEST(MathInterpbilinear, First)
{
    float xbounds[2] = { 0.0, 1.0 };
    float ybounds[2] = { 0.0, 1.0 };
    float vertex_vals[4] = { 0.0, 0.0, 0.0, 0.0 };

    float value = interpbilinear(vertex_vals, xbounds, ybounds, 0.5, 0.5);
    EXPECT_EQ(value, 0.0);
}

TEST(MathInterpbilinear, SlopedPlane1)
{
    float xbounds[2] = { 0.0, 1.0 };
    float ybounds[2] = { 0.0, 1.0 };
    float vertex_vals[4] = { 0.0, 0.0, 1.0, 1.0 };
    float value;

    value = interpbilinear(vertex_vals, xbounds, ybounds, 0.0, 0.5);
    EXPECT_EQ(value, 0.0);
    value = interpbilinear(vertex_vals, xbounds, ybounds, 1.0, 0.5);
    EXPECT_EQ(value, 1.0);
    value = interpbilinear(vertex_vals, xbounds, ybounds, 0.5, 0.0);
    EXPECT_EQ(value, 0.5);
    value = interpbilinear(vertex_vals, xbounds, ybounds, 0.5, 1.0);
    EXPECT_EQ(value, 0.5);
    value = interpbilinear(vertex_vals, xbounds, ybounds, 0.5, 0.5);
    EXPECT_EQ(value, 0.5);
}

TEST(MathInterpbilinear, SlopedPlane2)
{
    float xbounds[2] = { 0.0, 1.0 };
    float ybounds[2] = { 0.0, 1.0 };
    float vertex_vals[4] = { 0.0, 1.0, 1.0, 2.0 };
    float value;

    value = interpbilinear(vertex_vals, xbounds, ybounds, 0.0, 0.5);
    EXPECT_EQ(value, 0.5);

    value = interpbilinear(vertex_vals, xbounds, ybounds, 1.0, 0.5);
    EXPECT_EQ(value, 1.5);

    value = interpbilinear(vertex_vals, xbounds, ybounds, 0.5, 0.0);
    EXPECT_EQ(value, 0.5);

    value = interpbilinear(vertex_vals, xbounds, ybounds, 0.5, 1.0);
    EXPECT_EQ(value, 1.5);

    value = interpbilinear(vertex_vals, xbounds, ybounds, 0.5, 0.5);
    //printf ("value5 %4.2f\n", value);
    EXPECT_EQ(value, 1.0);
}


