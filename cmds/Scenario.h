// ================================================================
//  class Scenario
/** Scenario characteristics and state via dynamically loaded module.
 *  Allows for compiled behavior to be developed separately from the
 *  core system.
*/
// ================================================================

#ifndef _Scenario_h_
#define _Scenario_h_

#include "models/Vehicle.h"
#include "models/SimpleMotion.h"


struct AeroForces {
    float lift;         // newtons
    float drag;         // newtons
    float rotate;     // rate of upward rotation, rad/sec
};

class Scenario {
  //const std::string = "Scenario";
  protected:
    int initvars;       // don't need this; just exercising inits
    //SimpleMotionState* motion_st;
  public:
    Scenario() : initvars(0) {}

    virtual ~Scenario() {}

    void* getVehicle(char*);
    virtual const char* getName() = 0;

    // integration interfaces
    virtual void initcond() { }
    virtual void step() { }
    virtual bool moresteps() { return false; }
    virtual SimpleMotionState* getSimpleMotion() { return (SimpleMotionState*)0; };
};

typedef Scenario* scen_create_t();
typedef void scen_destroy_t(Scenario*);

#endif // _Scenario_h_
