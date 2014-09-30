// Protected data and software implementation for class Mat33d.

#ifndef _cart3_Mat33d_baseline_h_
#define _cart3_Mat33d_baseline_h_

#include <cmath>

namespace cart3 {

// basic constructors and destructors

inline Mat33d::Mat33d() { }

inline Mat33d::~Mat33d() { }

inline Mat33d::Mat33d(
        double s00, double s01, double s02,
        double s10, double s11, double s12,
        double s20, double s21, double s22)
{
    vec[0][0] = s00; vec[0][1] = s01; vec[0][2] = s02; vec[0][3] = 0.0;
    vec[1][0] = s10; vec[1][1] = s11; vec[1][2] = s12; vec[1][3] = 0.0;
    vec[2][0] = s20; vec[2][1] = s21; vec[2][2] = s22; vec[2][3] = 0.0;

}

inline Mat33d::Mat33d(Cart3d v0, Cart3d v1, Cart3d v2)
{
    vec[0] = v0; vec[1] = v1; vec[2] = v2;
}


// copy constructor

inline Mat33d&
Mat33d::operator = (const Mat33d& m)
{
    vec[0] = m.vec[0]; vec[1] = m.vec[1]; vec[2] = m.vec[2];
    return *this;
}

// compound assignment operators

inline Mat33d&
Mat33d::operator += (const Mat33d& m)
{
    vec[0] += m.vec[0]; vec[1] += m.vec[1]; vec[2] += m.vec[2];
    return *this;
}

inline Mat33d&
Mat33d::operator -= (const Mat33d& m)
{
    vec[0] -= m.vec[0]; vec[1] -= m.vec[1]; vec[2] -= m.vec[2];
    return *this;
}

inline Mat33d&
Mat33d::operator *= (const double s)
{
    vec[0] *= s; vec[1] *= s; vec[2] *= s;
    return *this;
}

inline Mat33d&
Mat33d::operator /= (const double s)
{
    double si = 1.0 / s;
    vec[0] *= si; vec[1] *= si; vec[2] *= si;
    return *this;
}

// index operators

inline Cart3d&
Mat33d::operator [] (int i)
{
    return vec[i];
}

inline Cart3d
Mat33d::operator [] (int i) const
{
    return vec[i];
}

// binary operators - additive

inline const Mat33d
Mat33d::operator + (const Mat33d& m) const
{
    Mat33d tmp;
    tmp.vec[0] = vec[0] + m.vec[0];
    tmp.vec[1] = vec[1] + m.vec[1];
    tmp.vec[2] = vec[2] + m.vec[2];
    return tmp;
}

inline const Mat33d
Mat33d::operator - (const Mat33d& m) const
{
    Mat33d tmp;
    tmp.vec[0] = vec[0] - m.vec[0];
    tmp.vec[1] = vec[1] - m.vec[1];
    tmp.vec[2] = vec[2] - m.vec[2];
    return tmp;
}

// binary operators - multiplicative

inline const Mat33d
Mat33d::operator * (double s) const
{
    Mat33d tmp;
    tmp.vec[0] = vec[0] * s;
    tmp.vec[1] = vec[1] * s;
    tmp.vec[2] = vec[2] * s;
    return tmp;
}

inline const Mat33d
Mat33d::operator / (double s) const
{
    // TODO: if 's' is zero, then should anticipate divide by zero.
    Mat33d tmp;
    double si;
    si = 1.0/s;
    tmp.vec[0] = vec[0] * si;
    tmp.vec[1] = vec[1] * si;
    tmp.vec[2] = vec[2] * si;
    return tmp;
}

// binary operators - multiplicative - dot products

inline const Cart3d
Mat33d::operator * (const Cart3d& v) const
{
    Cart3d tmp;

    for (int i=0; i<=dimen; ++i) {
        tmp[i] = vec[i][0]*v[0] + vec[i][1]*v[1] + vec[i][2]*v[2];
    }
    return tmp;
}

inline const Mat33d
Mat33d::operator * (const Mat33d& m) const
{
    // matrix dot product
    Mat33d tmp;

    for (int i=0; i<=dimen; ++i) {
        const Cart3d& row = vec[i];
        for (int j=0; j<=dimen; ++j) {
            Cart3d col = Cart3d(m.vec[j][0], m.vec[j][1], m.vec[j][2]);
            tmp.vec[i][j] = row * col;
        }
    }

    return tmp;
}

// unary operators

inline const Mat33d
Mat33d::operator - () const
{
    return (Mat33d(-vec[0], -vec[1], -vec[2]));
}

// comparison operators

inline bool
Mat33d::operator == (const Mat33d& m) const
{
    bool result;
    result = (
        (vec[0] == m.vec[0]) &&
        (vec[1] == m.vec[1]) &&
        (vec[2] == m.vec[2]));
    return result;
}

inline bool
Mat33d::operator != (const Mat33d& m) const
{
    bool result;
    result = (
        (vec[0] != m.vec[0]) ||
        (vec[1] != m.vec[1]) ||
        (vec[2] != m.vec[2]));
    return result;
}

} // namespace cart3

#endif // _cart3_Mat33d_baseline_h_

