// Protected data and software implementation for class Cart3d.

#ifndef _cart3_Cart3d_baseline_h_
#define _cart3_Cart3d_baseline_h_

#ifdef _CART3D_DATA_DEFN
#define _CART3D_DATA double elem[4]
    // Assist compiler in alignment; specify 4 instead of 3 elements.
#endif // _CART3D_DATA_DEFN

#include <cmath>

namespace cart3 {

// basic constructors and destructors

inline Cart3d::Cart3d() { }

inline Cart3d::~Cart3d() { }

inline Cart3d::Cart3d(double s0, double s1, double s2)
{
    elem[0] = s0; elem[1] = s1; elem[2] = s2;
}

// copy constructor

inline Cart3d&
Cart3d::operator = (const Cart3d& v)
{
    elem[0] = v.elem[0]; elem[1] = v.elem[1]; elem[2] = v.elem[2];
    return *this;
}

// compound assignment operators

inline Cart3d&
Cart3d::operator += (const Cart3d& v)
{
    elem[0] += v.elem[0]; elem[1] += v.elem[1]; elem[2] += v.elem[2];
    return *this;
}

inline Cart3d&
Cart3d::operator -= (const Cart3d& v)
{
    elem[0] -= v.elem[0]; elem[1] -= v.elem[1]; elem[2] -= v.elem[2];
    return *this;
}

inline Cart3d&
Cart3d::operator *= (const double s)
{
    elem[0] *= s; elem[1] *= s; elem[2] *= s; 
    return *this;
}

inline Cart3d&
Cart3d::operator /= (const double s)
{
    double si = 1.0 / s;
    elem[0] *= si; elem[1] *= si; elem[2] *= si; 
    return *this;
}

// index operators

inline double&
Cart3d::operator [] (int i)
{
    return elem[i];
}

inline double
Cart3d::operator [] (int i) const
{
    return elem[i];
}

// binary operators - additive

inline const Cart3d
Cart3d::operator + (const Cart3d& v) const
{
    Cart3d tmp;
    tmp.elem[0] = elem[0] + v.elem[0];
    tmp.elem[1] = elem[1] + v.elem[1];
    tmp.elem[2] = elem[2] + v.elem[2];
    return tmp;
}

inline const Cart3d
Cart3d::operator - (const Cart3d& v) const
{
    Cart3d tmp;
    tmp.elem[0] = elem[0] - v.elem[0];
    tmp.elem[1] = elem[1] - v.elem[1];
    tmp.elem[2] = elem[2] - v.elem[2];
    return tmp;
}

inline const Cart3d
Cart3d::operator * (double s) const
{
    Cart3d tmp;
    tmp.elem[0] = elem[0] * s;
    tmp.elem[1] = elem[1] * s;
    tmp.elem[2] = elem[2] * s;
    return tmp;
}

inline const Cart3d
Cart3d::operator / (double s) const
{
    // TODO: if 's' is zero, then should anticipate divide by zero.
    Cart3d tmp;
    double si;
    si = 1.0/s;
    tmp.elem[0] = elem[0] * si;
    tmp.elem[1] = elem[1] * si;
    tmp.elem[2] = elem[2] * si;
    return tmp;
}

inline const Cart3d
Cart3d::operator ^ (const Cart3d& v) const
{
    // cross product
    Cart3d tmp;
    tmp.elem[0] = elem[1] * v.elem[2];
    tmp.elem[1] = elem[2] * v.elem[0];
    tmp.elem[2] = elem[0] * v.elem[1];
    return tmp;
}

inline double
Cart3d::operator * (const Cart3d& v) const
{
    // dot product
    double tmp;
    tmp  = elem[0] * v.elem[0];
    tmp += elem[1] * v.elem[1];
    tmp += elem[2] * v.elem[2];
    return tmp;
}

inline Cart3d
operator * (const double s, const Cart3d& v)
{
    Cart3d tmp;
    tmp.elem[0] = v.elem[0] * s;
    tmp.elem[1] = v.elem[1] * s;
    tmp.elem[2] = v.elem[2] * s;
    return tmp;
}


// unary operators

inline const Cart3d
Cart3d::operator - () const
{
    return (Cart3d(-elem[0], -elem[1], -elem[2]));
}

// comparison operators

inline bool
Cart3d::operator == (const Cart3d& v) const
{
    bool result;
    result = (
        (elem[0] == v.elem[0]) &&
        (elem[1] == v.elem[1]) &&
        (elem[2] == v.elem[2]));
    return result;
}

inline bool
Cart3d::operator != (const Cart3d& v) const
{
    bool result;
    result = (
        (elem[0] != v.elem[0]) ||
        (elem[1] != v.elem[1]) ||
        (elem[2] != v.elem[2]));
    return result;
}

inline bool
Cart3d::operator < (const Cart3d& v) const
{
    bool result;
    result = (
        (elem[0] < v.elem[0]) &&
        (elem[1] < v.elem[1]) &&
        (elem[2] < v.elem[2]));
    return result;
}

// set value functions
//
inline void
Cart3d::set_zero()
{
    elem[0] = 0.0f; elem[1] = 0.0f; elem[2] = 0.0f;
}

inline void
Cart3d::set( double s0, double s1, double s2)
{
    elem[0] = s0; elem[1] = s1; elem[2] = s2;
}

inline void
Cart3d::set( const Cart3d& v)
{
    elem[0] = v.elem[0]; elem[1] = v.elem[1]; elem[2] = v.elem[2];
}

// length and normalization functions

inline double
Cart3d::length () const
{
    double l2 = length2();
    return sqrtf(l2);
}

inline double
Cart3d::length2 () const
{
    return elem[0]*elem[0] + elem[1]*elem[1] + elem[2]*elem[2];
}

inline double
Cart3d::normalize ()
{
    double len = sqrtf(length2());
    double si = 1.0f/len;
    elem[0] *= si;
    elem[1] *= si;
    elem[2] *= si;
    return len;
}

} // namespace cart3

#endif // _cart3_Cart3d_baseline_h_

