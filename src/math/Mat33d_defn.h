// ================================================================
// class Mat33d -- 3-dimensional Cartesian matrix
//   definition
// elements: IEEE single precision doubleing point
// ================================================================

#ifndef _cart3_Mat33d_defn_h_
#define _cart3_Mat33d_defn_h_

#include "math/Cart3d.h"

namespace cart3 {

// const int dimen = 3;

class Mat33d
{
  protected:
//#define _MAT33D_DATA Cart3d vec[3]
    _MAT33D_DATA;

  public:
    // basic constructors and destructors
    Mat33d();
    ~Mat33d();
    Mat33d(double s00, double s01, double s02,
           double s10, double s11, double s12,
           double s20, double s21, double s22);
    Mat33d(Cart3d v0, Cart3d v1, Cart3d v2);

    // copy constructor
    inline Mat33d& operator = (const Mat33d& m);

    // compound assignment operators
    inline Mat33d& operator += (const Mat33d& m);
    inline Mat33d& operator -= (const Mat33d& m);
    inline Mat33d& operator *= (const double s);
    inline Mat33d& operator /= (const double s);

    // index operators
    inline Cart3d& operator [] (int i);
    inline Cart3d operator [] (int i) const;

    // binary operators - additive
    inline const Mat33d operator + (const Mat33d& m) const;
    inline const Mat33d operator - (const Mat33d& m) const;

    // binary operators - multiplicative
    inline const Mat33d operator * (double s) const;
    inline const Mat33d operator / (double s) const;
    inline const Cart3d operator * (const Cart3d& v) const;
    inline const Mat33d operator * (const Mat33d& m) const;

    // unary operators
    inline const Mat33d operator - () const;

    // comparison operators
    inline bool operator == (const Mat33d& m) const;
    inline bool operator != (const Mat33d& m) const;

};    // class Mat33d

}    // namespace cart3

#endif // _cart3_Mat33d_defn_h_

