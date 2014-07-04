// atmostable.cc -- main program to run atmospheric table check
// Computing using SI units.

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "models/Atmos.h"

using namespace std;


// ================================================================
void SITable(FILE* fout)
{

    int i;
    float altKm;
    AtmosPropRatios ratios;
    AtmosProperties props;

    fprintf(fout, " alt    sigma      delta    theta");
    fprintf(fout, "  temp   press      dens     a   visc   k.visc\n" );
    fprintf(fout, "  Km                             ");
    fprintf(fout, "    K   N/sq.m    kg/cu.m  m/sec kg/m-s sq.m/s\n");

    for(i=-1; i<=43; i++) {
        altKm=2*i;                // changes int to float
        findAtmosPropRatios(altKm, &ratios);
        fprintf(fout, "%4i %8.4E %8.4E %6.4f", 2*i,
            ratios.sigma,ratios.delta,ratios.theta);
        findAtmosProperties(&ratios, &props);
        fprintf(fout, "%6.1f %8.3E %8.3E %5.1f",
            props.temperature, props.pressure, props.density, props.asound);
        fprintf(fout, "%6.2f %8.2E\n",
            1.0E6*props.viscosity, props.kinematicViscosity);
    }
}  // End of Procedure SITable


// ================================================================
int main(int argc, const char *argv[])
{
    FILE* fout;
    const char* fname;

    fname = argv[1];
    fout = fopen(fname, "w");
    SITable(fout);
    fclose(fout);
    return 0;
}

