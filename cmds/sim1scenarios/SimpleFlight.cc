// SimpleVehicle.cc
//  This is a simple module that confirms that the dynamic loading
//  interface is working.
//

#include <iostream>
#include <cmath>

#include "Scenario.h"
#include "models/SimpleMotion.h"

using std::string;
using std::abs;
#ifdef SIMPLEFLIGHT_DEBUG
using std::cout;
using std::endl;
#endif // SIMPLEFLIGHT_DEBUG

// output flags; match with SimEngine.cc
#define PUT_TRAJ        0x0001
#define PUT_AERO        0x0002
#define PUT_ATMOS       0x0100
#define PUT_GRAV        0x0200


#define STATEMAX        2
class SimpleFlight : public Scenario {
  protected:
    SimpleMotionState motionstate[STATEMAX];
    int currstate;

  public:
    void initcond();
    AeroForces getAeroForces(float density, float mach, float attack);

    const char* getName() { return "SimpleFlight"; }
    SimpleMotionState* getSimpleMotion();
    bool moresteps();
    unsigned int putnow(unsigned int forcemask = 0);

  private:

    // threshhold limits on run
    float tlimit;       // max time limit (want t<= tlimit)
    float hlimit;       // min height limit (want h >= hlimit)

    // output throttler
    float put_tnext;    // time
    float put_tintv;    // time interval
    float put_hatmos;   // atmos report height 
};

//  This code implements a simple of model of a falling body.
//  For simplicity, this can be imagined with the following initial
//  conditions:
//    * 10,000 meters above the reference surface.
//    * initial horizontal motion of 10 meters/sec.
//    * constant downward gravity of 10 meters/(sec^2).
//  Computation happens at 1 second intervals, and ends when either:
//    * 100 seconds have elapsed, or
//    * the body is within 1,000 meters of the surface.
//  Crude accuracy is provided at 1 second. Try 0.5 or 0.02 for more
//  interesting results.
//
void
SimpleFlight::initcond()
{
    currstate = 0;
    SimpleMotionState& ms = motionstate[currstate];

    tlimit = 100.0;
    hlimit = 1000.0;
    ms.x = Cart3f(0.0, 0.0, 10000.0);
    ms.dx = Cart3f(10.0, 0.0, 0.0);
    ms.ddx = Cart3f(0.0, 0.0, -9.8);
    ms.dt = 1.0;        // step-size
    put_tnext = 0.0;    // next scheduled put
    put_tintv = 5.0;    // interval
    put_hatmos = -10000.0;     // atmos report height; force first report
}

bool
SimpleFlight::moresteps()
{
    SimpleMotionState& ms = motionstate[currstate];
    bool moretime = ms.t <= tlimit;
    bool moreheight = ms.x[2] >= hlimit;

    return moretime && moreheight;
}

SimpleMotionState*
SimpleFlight::getSimpleMotion()
{
    int newstate = (currstate+1) % STATEMAX;
#ifdef SIMPLEFLIGHT_DEBUG
    cout << "newstate" << newstate << endl;
#endif // SIMPLEFLIGHT_DEBUG

    SimpleMotionState& cms = motionstate[currstate];
    SimpleMotionState& nms = motionstate[newstate];

    nms.ddx = cms.ddx;          // constant acceleration
    nms.dt = cms.dt;            // constant step-size
    nms.dx = cms.dx + nms.ddx * nms.dt;
    nms.x = cms.x + nms.dx * nms.dt;
    nms.t = cms.t + nms.dt;

    currstate = newstate;
    return &nms;
}

unsigned int
SimpleFlight::putnow(unsigned int forcemask)
{
    unsigned int put_flags = 0;
    SimpleMotionState& cms = motionstate[currstate];

    if (forcemask) {
        put_flags = forcemask;
    }

    if (cms.t > put_tnext) {
        put_flags |= PUT_TRAJ;
        put_tnext += put_tintv;
    }

    if (abs(cms.x[2] - put_hatmos) > 1000.0) {
        put_flags |= PUT_ATMOS;
        put_hatmos = cms.x[2];
    }

    return put_flags;
}


// class factories
extern "C" Scenario* create() { return new SimpleFlight; }
extern "C" void destroy(Scenario* s) { delete s; }

