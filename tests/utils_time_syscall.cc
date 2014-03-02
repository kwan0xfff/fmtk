// utils_time_syscall.cc -- representative small test computations

#include <cmath>
#include <stdio.h>
#include <gtest/gtest.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "utils/Timeval.h"

static void print_timeval(const char* msg, Timeval& tv)
{
    printf("%s %d.%06d\n", msg, tv.sec(), tv.usec());
}

void print_timeval(const char* msg, const timeval& tv)
{
    Timeval xtv = tv;
    print_timeval(msg, xtv);
}

TEST(Timeval, TODClock)
{
    Timeval tv_start, tv_finish;
    struct timeval now;
    (void)gettimeofday(&now, NULL);
    tv_start = Timeval(now);
    print_timeval("start ", tv_start);
    (void)gettimeofday(&now, NULL);
    tv_finish = Timeval(now);
    print_timeval("finish", tv_finish);
    Timeval diff = tv_finish - tv_start;
    EXPECT_GE(diff.usec(),  0);
}

TEST(Timeval, UsageClock)
{
    Timeval ustart, ufinish;
    Timeval sstart, sfinish;
    Timeval cum_utime, cum_stime;
    const bool print_cum = false;

    cum_utime = Timeval(0, 0);
    cum_stime = Timeval(0, 0);
    struct rusage ru;
    for (int i=0; i<=30; ++i) {

        getrusage(RUSAGE_SELF, &ru);
        ustart = Timeval(ru.ru_utime);
        sstart = Timeval(ru.ru_stime);

        getrusage(RUSAGE_SELF, &ru);
        ufinish = Timeval(ru.ru_utime);
        sfinish = Timeval(ru.ru_stime);

        EXPECT_EQ(true, (ustart <= ufinish));
        EXPECT_EQ(true, (sstart <= sfinish));
        cum_utime += (ufinish - ustart);
        cum_stime += (sfinish - sstart);
        if (i%10 == 0 && print_cum) {
            print_timeval("cum_utime", cum_utime);
            print_timeval("cum_stime", cum_stime);
        }
    }

}

