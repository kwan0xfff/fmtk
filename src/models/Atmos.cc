// Atmos.cc -- initial attempt at atmospheric info
// This code is currently focused on standard atmosphere for Earth.

#include <cmath>

#include "Atmos.h"

/*    P H Y S I C A L   C O N S T A N T S    */
static const float TZERO = 288.15;     // sea-level temperature, kelvins
static const float PZERO = 101325.0;   // sea-level pressure, N/sq.m
static const float RHOZERO = 1.225;    // sea-level density, kg/cu.m
static const float AZERO = 340.294;    // speed of sound at S.L. m/sec
static const float BETAVISC = 1.458E-6;// viscosity constant
static const float SUTH = 110.4;       // Sutherland's constant, kelvins


struct AtmosDatum stdAtmosEarth[] = {
    // Values are alt km, temp K, press N/sq.m, temp grad
    {  0.0, 288.15, 1.0,          -6.5 },
    { 11.0, 216.65, 2.2336110E-1,  0.0 },
    { 20.0, 216.65, 5.4032950E-2,  1.0 },
    { 32.0, 228.65, 8.5666784E-3,  2.8 },
    { 47.0, 270.65, 1.0945601E-3,  0.0 },
    { 51.0, 270.65, 6.6063531E-4, -2.8 },
    { 71.0, 214.65, 3.9046834E-5, -2.0 },
    { 84.852, 186.946, 3.68501E-6, 0.0 },
};
static int tablesz = sizeof(stdAtmosEarth)/sizeof(AtmosDatum);

const float REARTH=6369.0;        // radius of the Earth (km)
const float GMR = 34.163195;        // gas constant

// Compute ratios of temperature, density, and pressure.
// For Earth, this is the standard atmosphere, correct to 86 km.
// Only approximate thereafter.

//
//   altGM = geometric altitude
void
findAtmosPropRatios(const float altGM, AtmosPropRatios* ratios)
{
    int lo, hi, mid;
    float altGP, tgrad, deltah, tbase, tlocal;

    altGP=altGM*REARTH/(altGM+REARTH);  // geometric to geopotential altitude
    for (lo=0, hi=tablesz-1; hi > lo+1; ) {     // binary search
        mid=(lo+hi)/2;
        if (altGP < stdAtmosEarth[mid].height) hi=mid; else lo=mid;
    }
    int layer = lo;

    ratios->height = altGM;

    tgrad = stdAtmosEarth[layer].gradient;
    tbase = stdAtmosEarth[layer].temperature;
    deltah= altGP-stdAtmosEarth[layer].height;

    tlocal=tbase+tgrad*deltah;
    ratios->theta=tlocal/stdAtmosEarth[0].temperature; // temperature ratio

    if (tgrad == 0.0)                     // pressure ratio
        ratios->delta=stdAtmosEarth[layer].pressure*exp(-GMR*deltah/tbase);
    else
        ratios->delta=stdAtmosEarth[layer].pressure*pow(tbase/tlocal, GMR/tgrad);

    ratios->sigma= ratios->delta / ratios->theta;      // density ratio

}

// ================================================================
static float
MetricViscosity(const float theta)
{
  float t=theta*TZERO;                  // temperature in kelvins
  return BETAVISC*sqrt(t*t*t)/(t+SUTH); // viscosity in kg/(m-sec)
} // End of function MetricViscosity

// ================================================================

// Compute atmospheric values
void
findAtmosProperties(AtmosPropRatios* ratios, AtmosProperties* props)
{

    props->height = ratios->height;
    props->temperature = TZERO*ratios->theta;
    props->pressure = PZERO*ratios->delta;
    props->density = RHOZERO*ratios->sigma;
    props->asound = AZERO*sqrt(ratios->theta);
    props->viscosity = MetricViscosity(ratios->theta);
    props->kinematicViscosity = props->viscosity/props->density;
}



