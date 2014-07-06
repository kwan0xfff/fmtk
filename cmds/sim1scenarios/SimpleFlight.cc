// SimpleVehicle.cc
//  Currently, this a do-nothing module at confirms the interface is working.
//  It is intended to be a model of a simple object.
//

#include <iostream>
#include <cmath>

#include "Scenario.h"
#include "models/SimpleMotion.h"

using std::string;
// using vecmath::Cart3f;

class SimpleFlight : public Scenario {
  protected:

  public:
    void initcond();
    AeroForces getAeroForces(float density, float mach, float attack);

    const char* getName() { return "SimpleFlight"; }
    SimpleMotionState* getSimpleMotion();

  private:

};

// Initial conditions
void
SimpleFlight::initcond()
{
    // Need to decide this...
}

AeroForces
SimpleFlight::getAeroForces(float density, float mach, float attack)
{
    // should return following:  lift force, drag force, rotational speed
    AeroForces af;
    af.lift = 4.0;
    af.drag = 1.0;
    af.rotate = 0.0;

    return af;
}

SimpleMotionState*
SimpleFlight::getSimpleMotion()
{
    SimpleMotionState* motion_st = (SimpleMotionState*)0;
    // This is a dangling value; how is it computed...
    return motion_st;
}


// class factories
extern "C" Scenario* create() { return new SimpleFlight; }
extern "C" void destroy(Scenario* s) { delete s; }

