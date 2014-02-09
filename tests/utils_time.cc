// math_cart_baseline.cc -- reprsentative small test computations

#include <cmath>
#include <stdio.h>
#include <gtest/gtest.h>

#include "utils/Timeval.h"

static void print_timeval(Timeval& tv)
{
    printf("%d.%06d\n", tv.sec(), tv.usec());
}

void print_timeval(const timeval& tv)
{
    Timeval xtv = tv;
    print_timeval(xtv);
}

const Timeval tv_1_0 = Timeval(1, 0);
const Timeval tv_1_75 = Timeval(1, 750000);
const Timeval tv_2_0 = Timeval(2, 0);
const Timeval tv_2_5 = Timeval(2, 500000);
const Timeval tv_zero = Timeval(0, 0);

TEST(Timeval, First)
{
    Timeval a = Timeval(1, 2);
    EXPECT_EQ(a.sec(), 1);
    EXPECT_EQ(a.usec(), 2);
    print_timeval(a);
}

TEST(Timeval, CompoundAsgnAdd)
{
    Timeval sum =  tv_2_5;
    // simple add
    sum += tv_1_0;
    sum += tv_2_0;
    EXPECT_EQ(tv_2_5, Timeval(2, 500000));
    EXPECT_EQ(sum, Timeval(5, 500000));

    Timeval diff = tv_2_5;
    // simple subtract
    diff -= tv_1_0;
    EXPECT_EQ(diff, Timeval(1, 500000));

    // borrow from sec to usec
    diff = tv_2_0;
    diff -= tv_1_75;
    EXPECT_EQ(diff, Timeval(0, 250000));

}

TEST(Timeval, BinAdd)
{
    // simple add
    Timeval result = tv_2_5 + tv_1_0;
    EXPECT_EQ(result, Timeval(3, 500000));

    // carry from usec to sec
    result = tv_1_75 + tv_2_5;
    EXPECT_EQ(result, Timeval(4, 250000));

    // simple subtract
    result = tv_2_5 - tv_1_0;
    EXPECT_EQ(result, Timeval(1, 500000));

    // borrow from sec to usec
    result = tv_2_5 - tv_1_75;
    EXPECT_EQ(result, Timeval(0, 750000));

}

