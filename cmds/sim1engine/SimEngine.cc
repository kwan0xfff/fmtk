// SimEngine.cc -- a simulation engine
// Computing using SI units.
// This case is a hard-coded simulation until we figure out how to
// do otherwise.

#include <stdlib.h>
#include <dlfcn.h>
#include <iostream>
#include <cstdio>
#include <string>

#include "models/Atmos.h"
#include "models/FlightVehicle.h"
#include "models/SimpleMotion.h"
#include "utils/Writer.h"
#include "SimEngine.h"

#define LOGSUFFIX       ".log"
#ifndef DLSFX
#error DLSFX is not defined.
#endif

using namespace std;


// n is file handle number
void
SimEngine::setHandle(const int n, FILE* f) {
    switch (n) {
      case fnOut:
        fOut = f; break;
      case fnLog:
        fLog = f; break;
      default:
        fprintf(stderr, "setHandle failed\n");
        fflush(stderr);
        exit(1);
        break;
    }
}

Scenario*
SimEngine::loadScenario(const char* scenario_name) {
    //  void *scen_dyn;     // dynamic loading address
    //  Scenario *scen;
    bool load_fail = false;

    string module_name = string(scenario_name) + "." + DLSFX;

    scen_dyn = dlopen(module_name.c_str(), RTLD_LAZY);
    if (!scen_dyn) {
        cerr << "Cannot load scenario: " << dlerror() << '\n';
        cerr.flush();
        exit(EXIT_FAILURE);
    }

    // reset errors
    const char* dlsym_error;
    dlerror();

    // load the symbols
    dlscen_table.create =
            reinterpret_cast<scen_create_t*> (dlsym(scen_dyn, "create"));
    dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load Scenario symbol create: " << dlsym_error << endl;
        load_fail = true;
    }

    dlscen_table.destroy =
        reinterpret_cast<scen_destroy_t*> (dlsym(scen_dyn, "destroy"));
    dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load Scenario symbol destroy: " << dlsym_error << endl;
        load_fail = true;
    }

    if (load_fail) {
        exit(EXIT_FAILURE);
    }
    scen = dlscen_table.create();

    return scen;
}

void
SimEngine::unloadScenario() {
    dlscen_table.destroy(scen);
    dlclose(scen_dyn);
    cerr << "unloaded" << endl;
}

void
SimEngine::setScenario(const char* scenario_name) {
    scenario = scenario_name;
}


unsigned int
SimEngine::run() {

    Writer* writer = new Writer();
    writer->putmsg((const float)0.0, "veh1", "prolog", "start of new log");

    string logname = string(scenario) + LOGSUFFIX;
    fLog = fopen(logname.c_str(), "w");
    setHandle(SimEngine::fnLog, fLog);
    setHandle(SimEngine::fnOut, stdout);


    fprintf(fLog, "output to log\n");
    fprintf(stdout, "output to stdout\n");

    // Load the scenario module
    scen = loadScenario(scenario);
    cerr << scen->getName() << endl;

    // allow log to have CSV-like entries
    // headers.
    // step#, vehid, pos[0:2], world velo[0:2], veh velo[0:2], veh accel[0:2]
    SimpleMotionState* sms;
    scen->initcond();
    // INITIAL WRITE-OUT GOES HERE
    // initial step
    writer->initLine(0.0, "veh1", "traj");
    writer->putCart3Head("x", "0", "1", "2");
    writer->putCart3Head("dx", "0", "1", "2");
    writer->putCart3Head("ddx", "0", "1", "2");
    writer->finiLine();
#if 0
    writer->initLine(0.0, "veh1", "SMLD");
    writer->finiLine();
#endif /*0*/

    while (scen->moresteps()) {
        scen->step();
        sms = scen->getSimpleMotion();

        writer->initLine(sms->t, "veh1", "traj");
        writer->putCart3fLine(sms->x);
        writer->putCart3fLine(sms->dx);
        writer->putCart3fLine(sms->ddx);
        writer->finiLine();
#if 0
        writer->initLine(sms->t, "veh1", "SMLD");
        writer->finiLine();
#endif /*0*/

        // INCREMENTAL WRITE-OUT GOES HERE
        // flight angles
        // atmospheric conditions
        // summary
    }

    unloadScenario();

    return 0;
}

