// ================================================================
//  utility functions - rotation
//  Elements are:  IEEE double precision floating point
// ================================================================

#ifndef _math_rotate3d_h_
#define _math_rotate3d_h_

#include "Cart3d_defn.h"

namespace cart3 {

// rotations along the primary axes
Cart3d rotateX(float angle, Cart3d vec);
Cart3d rotateY(float angle, Cart3d vec);
Cart3d rotateZ(float angle, Cart3d vec);

};

#endif // _math_rotate3d_h_
