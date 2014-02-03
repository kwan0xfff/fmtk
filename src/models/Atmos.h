// ================================================================
//  class Atmos
//  Initial rudimentary model atmosphere code.
//   Uses standard atmosphere.
// ================================================================

#ifndef _models_Atmos_h_
#define _models_Atmos_h_

// AtmosDatum -- atmospheric data point
//   Used as transition point in std atmos models.
//   Normally resides in an atmospheric column.
struct AtmosDatum {
    float height;
    float temperature;
    float pressure;
    float gradient;
};

// AtmosPropRatios -- atmospheric property ratios compared to
// reference level (e.g. Earth sea level).
struct AtmosPropRatios {
    float height;
    float sigma;        // density compared to reference
    float delta;        // pressure compared to reference
    float theta;        // temperature compared to reference
};

// AtmosProperties -- properties expressed in target units
//   At height zero, this becomes reference values.
struct AtmosProperties {
    float height;
    float temperature;
    float pressure;
    float density;
    float asound;       // speed of sound
    float viscosity;
    float kinematicViscosity;
};

void
findAtmosPropRatios(
    const float alt,            // geometric altitude, km.
    AtmosPropRatios* ratios     // ratios
);

void
findAtmosProperties(
    AtmosPropRatios* ratios,    // ratios
    AtmosProperties* values     // values
);

#endif // _models_Atmos_h_
