//  ================================================================
//  bilinear interpolation
//
//  Given a rectangle bounded by sides xb[0], xb[1], yb[0], yb[1],
//  with values at vertices vx00, vx01, vx10, vx11,
//  interpolate the value at coordinates (x, y).
//  ================================================================

#ifndef _math_interpbilinear_
#define _math_interpbilinear_

enum { vx00=0, vx01, vx10, vx11, vx_sz };  // vertices

float
interpbilinear(const float v[], const float xb[], const float yb[], float x, float y);

#endif // _math_interpbilinear_
