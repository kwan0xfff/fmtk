// SimpleMotion.h
//
// Really simple, crude, and fast motion propagator.
// Single precision, Cartesian coordinates.
//

#ifndef _SimpleMotion_h
#define _SimpleMotion_h

#include "math/Cart3f.h"

using namespace cart3;

struct SimpleMotionState {
    Cart3f x, dx, ddx;          // pos, velo, accel
    float t, dt;                // time, time interval
};

class SimpleMotion {
  public:
    void integrate(SimpleMotionState* s0, SimpleMotionState* s1, bool addx=false);
    void integrate(SimpleMotionState& s0, SimpleMotionState& s1, bool addx=false);
};

#endif  // _SimpleMotion_h
