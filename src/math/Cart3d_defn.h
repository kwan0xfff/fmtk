// ================================================================
// class Cart3d -- 3-dimensional Cartesian vectors
//   definition
// elements: IEEE double precision floating point
// ================================================================

#ifndef _cart3_Cart3d_defn_h_
#define _cart3_Cart3d_defn_h_

namespace cart3 {

const int dimen = 3;

class Cart3d
{
  protected:
    _CART3D_DATA;

  public:
    // basic constructors and destructors
    Cart3d();
    ~Cart3d();
    Cart3d(double s0, double s1, double s2);

    // copy constructor
    inline Cart3d& operator = (const Cart3d& v);

    // compound assignment operators
    inline Cart3d& operator += (const Cart3d& v);
    inline Cart3d& operator -= (const Cart3d& v);
    inline Cart3d& operator *= (const double s);
    inline Cart3d& operator /= (const double s);

    // index operators
    inline double& operator [] (int i);
    inline double operator [] (int i) const;

    // binary operators - additive
    inline const Cart3d operator + (const Cart3d& v) const;
    inline const Cart3d operator - (const Cart3d& v) const;


    // binary operators - multiplicative
    inline const Cart3d operator * (double s) const;
    inline const Cart3d operator / (double s) const;
    inline const Cart3d operator ^ (const Cart3d& v) const; // cross product
    inline double operator * (const Cart3d& v) const;        // dot product
    inline friend Cart3d operator * (const double s, const Cart3d& v); // dot product

    // unary operators
    inline const Cart3d operator - () const;

    // comparison operators
    inline bool operator == (const Cart3d& v) const;
    inline bool operator != (const Cart3d& v) const;
    inline bool operator <  (const Cart3d& v) const;

    // set value functions
    inline void set_zero();
    inline void set( double s0, double s1, double s2);
    inline void set( const Cart3d& v);

    // length and normalization functions
    inline double length() const;
    inline double length2() const;
    inline double normalize();

};    // class Cart3d

}    // namespace cart3

#endif // _cart3_Cart3d_defn_h_

