// SimpleMotion.cc -- reprsentative test computations for motion

#include <iomanip>
#include <cmath>
#include <string>
#include "math/Cart3f.h"
#include "SimpleMotion.h"

using namespace cart3;

void
SimpleMotion::integrate(SimpleMotionState* s0, SimpleMotionState* s1, bool activeddx)
{
    s1->t = s0->dt + s0->t;     // timestamp
    s1->dt = s0->dt;            // step size
    if (! activeddx)
        s1->ddx = s0->ddx;      // assume constant acceleration
    // else s1->ddx should already be filled in.
    s1->dx = s0->ddx*s0->dt + s0->dx;
    s1->x = 0.5*s0->ddx*s0->dt*s0->dt + s0->dx*s0->dt + s0->x;
}

void
SimpleMotion::integrate(SimpleMotionState& s0, SimpleMotionState& s1, bool activeddx)
{
    s1.t = s0.dt + s0.t;     // timestamp
    s1.dt = s0.dt;            // step size
    if (! activeddx)
        s1.ddx = s0.ddx;      // assume constant acceleration
    // else s1.ddx should already be filled in.
    s1.dx = s0.ddx*s0.dt + s0.dx;
    s1.x = 0.5*s0.ddx*s0.dt*s0.dt + s0.dx*s0.dt + s0.x;
}
