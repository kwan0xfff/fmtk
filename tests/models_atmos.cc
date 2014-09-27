// models_atmos.cc -- representative small test computations

#include <cmath>
#include <cstdlib>      // includes abs()
#include <stdio.h>
#include <gtest/gtest.h>

#include "models/Atmos.h"

void
printRatios(AtmosPropRatios ratios) {
    printf("%4.1f %8.4E %8.4E %6.4f\n", ratios.height,
        ratios.sigma,ratios.delta,ratios.theta);
}

void
printProperties(AtmosProperties props) {
    printf("%10.5f %12.7E %12.7E %9.4f\n",
        props.temperature, props.pressure, props.density, props.asound);
    printf("%6.2f %8.2E\n",
        1.0E6*props.viscosity, props.kinematicViscosity);
}

// epsilon uncerainty -- 10 to minus X power
float epsM[] = { 1, 1.0e-1, 1.0e-2, 1.0e-3, 1.0e-4, 1.0e-5, 1.0e-6 };

TEST(Models, Atmos0)
{
    AtmosPropRatios ratios;
    AtmosProperties props;
    float altKm = 0.0;

    findAtmosPropRatios(altKm, &ratios);
    findAtmosProperties(&ratios, &props);
    //printRatios(ratios);
    //printProperties (props);

    EXPECT_NEAR(ratios.sigma, 1.0, epsM[6]);
    EXPECT_NEAR(ratios.delta, 1.0, epsM[6]);
    EXPECT_NEAR(ratios.theta, 1.0, epsM[6]);

    EXPECT_NEAR(props.temperature, 288.1, epsM[1]);
    EXPECT_NEAR(props.pressure, 101325.0, epsM[0]);
    EXPECT_NEAR(props.density, 1.225, epsM[2]);
    EXPECT_NEAR(props.asound, 340.294, epsM[2]);
}

TEST(Models, Atmos5)
{
    AtmosPropRatios ratios;
    AtmosProperties props;
    float altKm = 5.0;

    findAtmosPropRatios(altKm, &ratios);
    findAtmosProperties(&ratios, &props);

    EXPECT_NEAR(ratios.sigma, 0.60117, epsM[5]);
    EXPECT_NEAR(ratios.delta, 0.53341, epsM[5]);
    EXPECT_NEAR(ratios.theta, 0.8873, epsM[5]);

    EXPECT_NEAR(props.temperature, 255.675, epsM[2]);
    EXPECT_NEAR(props.pressure, 54048.2, epsM[0]);
    EXPECT_NEAR(props.density, 0.7364, epsM[4]);
    EXPECT_NEAR(props.asound, 320.545, epsM[2]);
}

TEST(Models, Atmos25)
{
    AtmosPropRatios ratios;
    AtmosProperties props;
    float altKm = 25.0;

    findAtmosPropRatios(altKm, &ratios);
    findAtmosProperties(&ratios, &props);
    //printRatios(ratios);
    //printProperties (props);

    EXPECT_NEAR(ratios.sigma, 0.032721, epsM[5]);
    EXPECT_NEAR(ratios.delta, 0.025158, epsM[5]);
    EXPECT_NEAR(ratios.theta, 0.7689, epsM[4]);

    EXPECT_NEAR(props.temperature, 221.552, epsM[2]);
    EXPECT_NEAR(props.pressure, 2549.1, epsM[1]);
    EXPECT_NEAR(props.density, 0.04008, epsM[4]);
    EXPECT_NEAR(props.asound, 298.3892, epsM[3]);
}

