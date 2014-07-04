// Protected data and software implementation for class Cart3f.

#ifndef _cart_Cart3f_baseline_h_
#define _cart_Cart3f_baseline_h_

#ifdef _CART3F_DATA_DEFN
#define _CART3F_DATA float elem[4]
    // Align data on 16-byte boundary, but really use 12 bytes
#endif // _CART3F_DATA_DEFN

#include <cmath>

namespace cart3 {

// basic constructors and destructors

inline Cart3f::Cart3f() { }

inline Cart3f::~Cart3f() { }

inline Cart3f::Cart3f(float s0, float s1, float s2)
{
    elem[0] = s0; elem[1] = s1; elem[2] = s2;
}

// copy constructor

inline Cart3f&
Cart3f::operator = (const Cart3f& v)
{
    elem[0] = v.elem[0]; elem[1] = v.elem[1]; elem[2] = v.elem[2];
    return *this;
}

// compound assignment operators

inline Cart3f&
Cart3f::operator += (const Cart3f& v)
{
    elem[0] += v.elem[0]; elem[1] += v.elem[1]; elem[2] += v.elem[2];
    return *this;
}

inline Cart3f&
Cart3f::operator -= (const Cart3f& v)
{
    elem[0] -= v.elem[0]; elem[1] -= v.elem[1]; elem[2] -= v.elem[2];
    return *this;
}

inline Cart3f&
Cart3f::operator *= (const float s)
{
    elem[0] *= s; elem[1] *= s; elem[2] *= s; 
    return *this;
}

inline Cart3f&
Cart3f::operator /= (const float s)
{
    float si = 1.0 / s;
    elem[0] *= si; elem[1] *= si; elem[2] *= si; 
    return *this;
}

// index operators

inline float&
Cart3f::operator [] (int i)
{
    return elem[i];
}

inline float
Cart3f::operator [] (int i) const
{
    return elem[i];
}

// binary operators - additive

inline const Cart3f
Cart3f::operator + (const Cart3f& v) const
{
    Cart3f tmp;
    tmp.elem[0] = elem[0] + v.elem[0];
    tmp.elem[1] = elem[1] + v.elem[1];
    tmp.elem[2] = elem[2] + v.elem[2];
    return tmp;
}

inline const Cart3f
Cart3f::operator - (const Cart3f& v) const
{
    Cart3f tmp;
    tmp.elem[0] = elem[0] - v.elem[0];
    tmp.elem[1] = elem[1] - v.elem[1];
    tmp.elem[2] = elem[2] - v.elem[2];
    return tmp;
}

inline const Cart3f
Cart3f::operator * (float s) const
{
    Cart3f tmp;
    tmp.elem[0] = elem[0] * s;
    tmp.elem[1] = elem[1] * s;
    tmp.elem[2] = elem[2] * s;
    return tmp;
}

inline const Cart3f
Cart3f::operator / (float s) const
{
    // TODO: if 's' is zero, then should anticipate divide by zero.
    Cart3f tmp;
    float si;
    si = 1.0/s;
    tmp.elem[0] = elem[0] * si;
    tmp.elem[1] = elem[1] * si;
    tmp.elem[2] = elem[2] * si;
    return tmp;
}

inline const Cart3f
Cart3f::operator ^ (const Cart3f& v) const
{
    // cross product
    Cart3f tmp;
    tmp.elem[0] = elem[1] * v.elem[2];
    tmp.elem[1] = elem[2] * v.elem[0];
    tmp.elem[2] = elem[0] * v.elem[1];
    return tmp;
}

inline float
Cart3f::operator * (const Cart3f& v) const
{
    // dot product
    float tmp;
    tmp  = elem[0] * v.elem[0];
    tmp += elem[1] * v.elem[1];
    tmp += elem[2] * v.elem[2];
    return tmp;
}

inline Cart3f
operator * (const float s, const Cart3f& v)
{
    Cart3f tmp;
    tmp.elem[0] = v.elem[0] * s;
    tmp.elem[1] = v.elem[1] * s;
    tmp.elem[2] = v.elem[2] * s;
    return tmp;
}


// unary operators

inline const Cart3f
Cart3f::operator - () const
{
    return (Cart3f(-elem[0], -elem[1], -elem[2]));
}

// comparison operators

inline bool
Cart3f::operator == (const Cart3f& v) const
{
    bool result;
    result = (
        (elem[0] == v.elem[0]) &&
        (elem[1] == v.elem[1]) &&
        (elem[2] == v.elem[2]));
    return result;
}

inline bool
Cart3f::operator != (const Cart3f& v) const
{
    bool result;
    result = (
        (elem[0] != v.elem[0]) ||
        (elem[1] != v.elem[1]) ||
        (elem[2] != v.elem[2]));
    return result;
}

inline bool
Cart3f::operator < (const Cart3f& v) const
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
Cart3f::set_zero()
{
    elem[0] = 0.0f; elem[1] = 0.0f; elem[2] = 0.0f;
}

inline void
Cart3f::set( float s0, float s1, float s2)
{
    elem[0] = s0; elem[1] = s1; elem[2] = s2;
}

inline void
Cart3f::set( const Cart3f& v)
{
    elem[0] = v.elem[0]; elem[1] = v.elem[1]; elem[2] = v.elem[2];
}

// length and normalization functions

inline float
Cart3f::length () const
{
    float l2 = length2();
    return sqrtf(l2);
}

inline float
Cart3f::length2 () const
{
    return elem[0]*elem[0] + elem[1]*elem[1] + elem[2]*elem[2];
}

inline float
Cart3f::normalize ()
{
    float len = sqrtf(length2());
    float si = 1.0f/len;
    elem[0] *= si;
    elem[1] *= si;
    elem[2] *= si;
    return len;
}

} // namespace cart3

#endif // _cart_Cart3f_baseline_h_

