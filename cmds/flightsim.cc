// flightsim.cc -- main program to do an example flight sim
// Computing using SI units.

#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <string>

#include "models/Atmos.h"
#include "models/FlightVehicle.h"
#include "models/SimpleMotion.h"
#include "SimEngine.h"
#include "Scenario.h"

using namespace std;

int main(int argc, const char *argv[]) {
    const char* scenarioname;

    SimEngine* sim;

    scenarioname = argv[1];    // scenario name

    // For now, use a single engine for a single flight.
    // In the future, there may be multiple engines for
    // differing scenarios.

    sim = new SimEngine();
    sim->setScenario(scenarioname);
    sim->run();

    return 0;
}

