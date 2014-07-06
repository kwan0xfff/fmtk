// ================================================================
//  utility functions Rotate3f
//  Elements are:  IEEE single precision floating point
// ================================================================

#ifndef _math_rotate3f_h_
#define _math_rotate3f_h_

#include "Cart3f_defn.h"

namespace cart3 {

// rotations along the primary axes
Cart3f rotateX(float angle, Cart3f vec);
Cart3f rotateY(float angle, Cart3f vec);
Cart3f rotateZ(float angle, Cart3f vec);

};

#endif // _math_rotate3f_h_
