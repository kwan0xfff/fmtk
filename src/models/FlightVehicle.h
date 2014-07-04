// ================================================================
//  class Vehicle
/** Vehicle characteristics and state.
    ....
*/
// ================================================================

#ifndef _FlightVehicle_h_
#define _FlightVehicle_h_

#include "Vehicle.h"
#include "math/Cart3f.h"
#include <string>

using std::string;
using namespace cart3;

class FlightVehicle : public Vehicle {
  public:
    const string getName();
    void setName(std::string );

    // forces relative to air free stream against vehicle
    Cart3f fAero;               // aero forces: drag = -x, lift = z
    // forces relative to vehicle axes
    Cart3f fPropul;             // propulsion
    float mass;
    float aClimb;               // angle of trajectory to ground, radians
        // probably should be decomposed to theta and phi
    float aAttack;              // angle of vehicle reference to traj.
    // above assumes static atmospheric conditions
    // thrust is exactly aligned with vehicle 

    float cLift, cDrag;         // coeffs of lift and drag
    float speed;                // meters/sec
    float aMach;                // Mach number
    float h;                    // altitude, meters
    float qDyn;                 // dynamic pressure

    // some temporary numbers
    float massflow;
    float thrust;

    // flight segment parameters
    float aTrajDegTarget;       // desired trajectory angle, degrees
    float aAttackDegMax;        // max angle of attack, degrees
    float planarea;             // planview area - for lift/drag

  private:
    std::string vehname;           // vehicle name
    // PropulsionSystem mainprop;
    // map<string, PropulsionSystem> auxprop;
    // GNC
};

#endif // _FlightVehicle_h_
