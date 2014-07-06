// ================================================================
//  class SimEngine
/** SimEngine characteristics and state.
    ....
*/
// ================================================================

#ifndef _SimEngine_h_
#define _SimEngine_h_

#include "models/Vehicle.h"
#include "Scenario.h"

#include <cstdio>
#include <string>

class SimEngine {
  //const std::string = "SimEngine";
  public:
    static const int fnOut = 1;
    static const int fnLog = 3;

    void setScenario(const char* sn);   // set name
    unsigned int run();

    // const std::string* getName();
    void setHandle(const int, FILE*);
    Scenario* loadScenario(const char* sn);
    void unloadScenario();

    Vehicle* vehicle;           // We should really support multiple vehicles via map.

  private:
    // float drymass;
    // PropulsionSystem mainprop;
    // map<string, PropulsionSystem> auxprop;
    // GNC
    FILE* fOut;         // output file handle
    FILE* fLog;         // log handle
    const char* scenario;       // scenario name

    double sim_time, dt;        // simulation time, step size

    // vehicle module access points (via dlopen)
    struct _vehicle {
        void initcond();

    } veh;
    struct {
        scen_create_t* create;
        scen_destroy_t* destroy;
    } dlscen_table;
    Scenario* scen;
    void* scen_dyn;
};



#endif // _SimEngine_h_
