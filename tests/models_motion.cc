// models_atmos.cc -- representative small test computations

#include <cmath>
#include <cstdlib>      // includes abs()
#include <stdio.h>
#include <gtest/gtest.h>

#include "models/SimpleMotion.h"

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
#endif //0

const Cart3f z_1e3 = Cart3f(0.0, 0.0, 1000.0);
const Cart3f z_1e2 = Cart3f(0.0, 0.0,  100.0);
const Cart3f z_1e1 = Cart3f(0.0, 0.0,   10.0);
const Cart3f z_1e0 = Cart3f(0.0, 0.0,    1.0);
const Cart3f zero  = Cart3f(0.0, 0.0,    0.0);

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

    ms.x = z_1e3;
    ms.dx = z_1e2;
    ms.ddx = zero;
    ms.dt = 0.2;        // step-size
    //print_cart3f(ms.dx);
    motion.setState(ms);

    for (int i=0; i<10; ++i) {
        motion.step();
        ms = motion.getState();
        //print_cart3f(ms.x);
    }
    ms = motion.getState();

    EXPECT_LE(ms.x[0], 0.0);
    EXPECT_LE(fabs(ms.x[2]-1200.0), epsM[5]);
}

