// models_atmos.cc -- representative small test computations

#include <cmath>
#include <cstdlib>      // includes abs()
#include <stdio.h>
#include <gtest/gtest.h>

#include "models/SimpleMotion.h"


// epsilon uncerainty -- 10 to minus X power
float epsM[] = { 1, 1.0e-1, 1.0e-2, 1.0e-3, 1.0e-4, 1.0e-5, 1.0e-6 };

#define STATEMAX        2
struct Motion {
  private:
    SimpleMotionState motionstate[STATEMAX];
    int currstate;
    SimpleMotion* motion;       // integrator

  public:
    Motion();
    ~Motion();
    void step();
    SimpleMotionState& getState() { return motionstate[currstate]; }
    void setState(SimpleMotionState& sms) { motionstate[currstate] = sms; }
};

Motion::Motion()
{
    currstate = 0;
    motion = new SimpleMotion();
}

Motion::~Motion()
{
    delete motion;
}

void
Motion::step()
{
    SimpleMotionState& m0 = motionstate[currstate];
    currstate = (currstate+1) % STATEMAX;
    SimpleMotionState& m1 = motionstate[currstate];
    motion->integrate(m0, m1);
}

TEST(Models, MotionSimp1)
{
    Motion motion;
    SimpleMotionState ms;

    ms.x = Cart3f(0.0, 0.0, 1000.0);
    ms.dx = Cart3f(0.0, 0.0, 100.0);
    ms.ddx = Cart3f(0.0, 0.0, 0.0);
    ms.dt = 0.2;        // step-size
    motion.setState(ms);

    for (int i=0; i<10; ++i) {
        motion.step();
    }
    ms = motion.getState();

    EXPECT_LE(ms.x[0], 0.0);
    EXPECT_LE(fabs(ms.x[2]-1200.0), epsM[5]);
}
