#include "Timeval.h"

//static const int ZERO = 0;
static const int MILLION = 1000000;
static const int TWOMILLION = 2 * MILLION;

#if 0
#include <stdio.h>
static void print_timeval(const char* msg, const Timeval& tv)
{
    printf("%s %d.%06d\n", msg, tv.sec(), tv.usec());
}
#endif

// compound assignment operators

Timeval&
Timeval::operator += (const Timeval& tv)
{
    const struct timeval& ext = tv._v;

    _v.tv_usec += ext.tv_usec;
    _v.tv_sec += ext.tv_sec;
    if (_v.tv_usec >= MILLION) {
        // Normalize so that _v.tv_usec < 1000000.
        int remainder = _v.tv_usec % MILLION;

        if (_v.tv_usec < TWOMILLION) {
            _v.tv_sec += 1;
        } else {
            // This should only happen if "ext" not pre-normalized.
            int quotient = _v.tv_usec / MILLION;
            _v.tv_sec += quotient;
        }
        _v.tv_usec = remainder;
    }
    return *this;
}

Timeval&
Timeval::operator -= (const Timeval& tv)
{
    const struct timeval& ext = tv._v;

    if (_v.tv_usec < ext.tv_usec) {
        _v.tv_sec -= 1;
        _v.tv_usec += MILLION;
    }
    _v.tv_usec -= ext.tv_usec;
    _v.tv_sec -= ext.tv_sec;
    return *this;
}

// binary operators - additive

const Timeval
Timeval::operator + (const Timeval& tv) const
{
    const struct timeval& ext = tv._v;
    Timeval tmp;

    //print_timeval("+  this ", *this);
    //print_timeval("+  other", tv);

    tmp._v.tv_usec = _v.tv_usec + ext.tv_usec;
    tmp._v.tv_sec = _v.tv_sec + ext.tv_sec;

    if (tmp._v.tv_usec >= MILLION) {
        // Normalize so that tmp._v.tv_usec < 1000000.
        int remainder = tmp._v.tv_usec % MILLION;

        if (tmp._v.tv_usec < TWOMILLION) {
            tmp._v.tv_sec += 1;
        } else {
            // This should only happen if "ext" not pre-normalized.
            int quotient = tmp._v.tv_usec / MILLION;
            tmp._v.tv_sec += quotient;
        }
        tmp._v.tv_usec = remainder;
    }
    //print_timeval("+ result", tmp);
    return tmp;
}

const Timeval
Timeval::operator - (const Timeval& tv) const
{
    const struct timeval& ext = tv._v;
    Timeval tmp;

    if (_v.tv_usec < ext.tv_usec) {
        tmp._v.tv_usec = _v.tv_usec + MILLION - ext.tv_usec;
        tmp._v.tv_sec = _v.tv_sec - 1 - ext.tv_sec;
    } else {
        tmp._v.tv_usec = _v.tv_usec - ext.tv_usec;
        tmp._v.tv_sec = _v.tv_sec - ext.tv_sec;
    }
    return tmp;
}

// comparison operators
bool
Timeval::operator == (const Timeval& tv) const
{
    const struct timeval& ext = tv._v;
    bool result = (
        (_v.tv_sec == ext.tv_sec) && (_v.tv_usec == ext.tv_usec));
    return result;
}

bool
Timeval::operator != (const Timeval& tv) const
{
    const struct timeval& ext = tv._v;
    bool result = (
        (_v.tv_usec != ext.tv_usec) || (_v.tv_usec != ext.tv_usec));

    return result;
}

bool
Timeval::operator < (const Timeval& tv) const
{
    const struct timeval& ext = tv._v;
    Timeval tmp;
    bool result;

    if (_v.tv_sec < ext.tv_sec) {
        result = true;
    } else if (_v.tv_sec > ext.tv_sec) {
        result = false;
    } else {    // _v.tv_sec == ext.tv_sec
        result = (_v.tv_usec < ext.tv_usec) ? true : false ;
    }

    return result;
}

bool
Timeval::operator <= (const Timeval& tv) const
{
    const struct timeval& ext = tv._v;
    Timeval tmp;
    bool result;

    if (_v.tv_sec < ext.tv_sec) {
        result = true;
    } else if (_v.tv_sec > ext.tv_sec) {
        result = false;
    } else {    // _v.tv_sec == ext.tv_sec
        result = (_v.tv_usec <= ext.tv_usec) ? true : false ;
    }

    return result;
}

