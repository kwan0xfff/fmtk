// ================================================================
// class Cart3f -- 3-dimensional Cartesian vectors
//   definition
// elements: IEEE single precision floating point
// ================================================================

#ifndef _cart3_Cart3f_defn_h_
#define _cart3_Cart3f_defn_h_

namespace cart3 {

const int dimen = 3;

class Cart3f
{
  protected:
    _CART3F_DATA;

  public:
    // basic constructors and destructors
    Cart3f();
    ~Cart3f();
    Cart3f(float s0, float s1, float s2);

    // copy constructor
    inline Cart3f& operator = (const Cart3f& v);

    // compound assignment operators
    inline Cart3f& operator += (const Cart3f& v);
    inline Cart3f& operator -= (const Cart3f& v);
    inline Cart3f& operator *= (const float s);
    inline Cart3f& operator /= (const float s);

    // index operators
    inline float& operator [] (int i);
    inline float operator [] (int i) const;

    // binary operators - additive
    inline const Cart3f operator + (const Cart3f& v) const;
    inline const Cart3f operator - (const Cart3f& v) const;


    // binary operators - multiplicative
    inline const Cart3f operator * (float s) const;
    inline const Cart3f operator / (float s) const;
    inline const Cart3f operator ^ (const Cart3f& v) const; // cross product
    inline float operator * (const Cart3f& v) const;        // dot product

    // unary operators
    inline const Cart3f operator - () const;

    // comparison operators
    inline bool operator == (const Cart3f& v) const;
    inline bool operator != (const Cart3f& v) const;
    inline bool operator <  (const Cart3f& v) const;

    // set value functions
    inline void set_zero();
    inline void set( float s0, float s1, float s2);
    inline void set( const Cart3f& v);

    // length and normalization functions
    inline float length() const;
    inline float length2() const;
    inline float normalize();

};    // class Cart3f

}    // namespace cart3

#endif // _cart3_Cart3f_defn_h_

