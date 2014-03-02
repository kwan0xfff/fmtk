//  ================================================================
//  class Timeval
//    Arithmetic using POSIX 'struct timeval'.
//    Compound struct timeval values are generated by getrusage().
//    Timeval operations are defined for non-negative values.
//  ================================================================

#ifndef _utils_Timeval_h_
#define _utils_Timeval_h_

#include <sys/resource.h>

class Timeval
{
  private:
    timeval _v;
  public:
    // basic constructors and destructors
    Timeval() { };
    ~Timeval() { };
    inline Timeval(int sec, int usec) {
        _v.tv_sec = sec; _v.tv_usec = usec;
    }
    inline Timeval(timeval tv) { _v = tv; }

    // copy constructor
    inline Timeval& operator = (const Timeval& tv) {
        _v.tv_sec = tv._v.tv_sec; _v.tv_usec = tv._v.tv_usec;
        return *this;
    }

    // compound assignment operators
    Timeval& operator += (const Timeval& tv);
    Timeval& operator -= (const Timeval& tv);
    //
    // binary operators - additive
    const Timeval operator + (const Timeval& tv) const;
    const Timeval operator - (const Timeval& tv) const;

    // comparison operators
    bool operator == (const Timeval& tv) const;
    bool operator != (const Timeval& tv) const;
    bool operator < (const Timeval& tv) const;
    bool operator <= (const Timeval& tv) const;

    // set, get
    inline void zero() { _v.tv_sec = 0; _v.tv_usec = 0; }
    int sec() const { return _v.tv_sec; }
    int usec() const { return _v.tv_usec; }

};

#endif // _utils_Timeval_h_

