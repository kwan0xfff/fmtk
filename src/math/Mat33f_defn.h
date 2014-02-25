// ================================================================
// class Mat33f -- 3-dimensional Cartesian matrix
//   definition
// elements: IEEE single precision floating point
// ================================================================

#ifndef _cart3_Mat33f_defn_h_
#define _cart3_Mat33f_defn_h_

#include "math/Cart3f.h"

namespace cart3 {

// const int dimen = 3;

class Mat33f
{
  protected:
//#define _MAT33F_DATA Cart3f vec[3]
    _MAT33F_DATA;

  public:
    // basic constructors and destructors
    Mat33f();
    ~Mat33f();
    Mat33f(float s00, float s01, float s02,
           float s10, float s11, float s12,
           float s20, float s21, float s22);
    Mat33f(Cart3f v0, Cart3f v1, Cart3f v2);

    // copy constructor
    inline Mat33f& operator = (const Mat33f& m);

    // compound assignment operators
    inline Mat33f& operator += (const Mat33f& m);
    inline Mat33f& operator -= (const Mat33f& m);
    inline Mat33f& operator *= (const float s);
    inline Mat33f& operator /= (const float s);

    // index operators
    inline Cart3f& operator [] (int i);
    inline Cart3f operator [] (int i) const;

    // binary operators - additive
    inline const Mat33f operator + (const Mat33f& m) const;
    inline const Mat33f operator - (const Mat33f& m) const;

    // binary operators - multiplicative
    inline const Mat33f operator * (float s) const;
    inline const Mat33f operator / (float s) const;
    inline const Cart3f operator * (const Cart3f& v) const;
    inline const Mat33f operator * (const Mat33f& m) const;

    // unary operators
    inline const Mat33f operator - () const;

    // comparison operators
    inline bool operator == (const Mat33f& m) const;
    inline bool operator != (const Mat33f& m) const;

};    // class Mat33f

}    // namespace cart3

#endif // _cart3_Mat33f_defn_h_

