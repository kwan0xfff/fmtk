// rotate3d
/* Assumes right-hand rule axes.
 *  Rather than notation [x, y, z], the code here simply adopts indices [0, 1, 2].
 *
 *  CAUTION: Rotating a vector in an inertial frame and space is not the same as
 *  rotating a reference frame while leaving the vector alone in inertial space.
 */

#include <cmath>
#include "Cart3d.h"
#include "rotate3d.h"

namespace cart3 {
//  A template for transform matrix element alignment; otherwise it is gibberish.
//  vn[n] = - scn_a*v0[0] + scn_a*v0[1] + scn_a*v0[2];

// confirmed math
// rotateX - rotation along X axis (vn[0])
Cart3d rotateX(float angle, Cart3d vec)
{
    Cart3d& v0 = vec;
    Cart3d v1;
    float sin_a, cos_a;

    sin_a = sin(angle);
    cos_a = cos(angle);

    v1[0] =         v0[0];
    v1[1] =                 cos_a*v0[1] + sin_a*v0[2];
    v1[2] =               - sin_a*v0[1] + cos_a*v0[2];

    return v1;
}

// rotateY - rotation along Y axis (vn[1])
Cart3d rotateY(float angle, Cart3d vec)
{
    Cart3d& v0 = vec;
    Cart3d v1;
    float sin_a, cos_a;

    sin_a = sin(angle);
    cos_a = cos(angle);

    v1[0] =   cos_a*v0[0]               - sin_a*v0[2];
    v1[1] =                       v0[1];
    v1[2] =   sin_a*v0[0]               + cos_a*v0[2];

    return v1;
}

// rotateZ - rotation along Z axis (vn[2])
Cart3d rotateZ(float angle, Cart3d vec)
{
    Cart3d& v0 = vec;
    Cart3d v1;
    float sin_a, cos_a;

    sin_a = sin(angle);
    cos_a = cos(angle);

    v1[0] =   cos_a*v0[0] + sin_a*v0[1];
    v1[1] = - sin_a*v0[0] + cos_a*v0[1];
    v1[2] =                                     v0[2];

    return v1;
}

} // namespace vecmath


