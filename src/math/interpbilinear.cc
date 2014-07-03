//  binear interpolation
//
//  Implementation loosely based on the algorithm at:
//  http://en.wikipedia.org/wiki/Bilinear_interpolation
//

#include "interpbilinear.h"

float
interpbilinear(const float v[], const float xb[], const float yb[], float x, float y)
{
    float weights =
        v[vx00] * (xb[1]-x) * (yb[1]-y) +
        v[vx01] * (xb[1]-x) * (y-yb[0]) +
        v[vx10] * (x-xb[0]) * (yb[1]-y) +
        v[vx11] * (x-xb[0]) * (y-yb[0]);
    float area = (xb[1]-xb[0]) * (yb[1]-yb[0]);

    float value = weights / area;

    return value;
}
