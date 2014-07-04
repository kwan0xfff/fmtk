// FlightVehicle.cc

#include <iostream>
#include <cmath>

#include "Atmos.h"
#include "FlightVehicle.h"

using std::string;

const string
FlightVehicle::getName()
{
    return vehname;
}

void
FlightVehicle::setName(string name)
{
    vehname = name;
}


