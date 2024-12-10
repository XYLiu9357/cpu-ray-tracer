/**ray.hpp
* 
* Ray class.
*
*/

#ifndef RAY_H
#define RAY_H

#include "utils/vec3.hpp"

class Ray {
private:
    Point3 orig;
    Vec3 dir;

public:
    Ray();
    Ray(const Point3& origin, const Vec3& direction);
    const Point3& origin() const;
    const Vec3& direction() const;
    Point3 at(double t) const;
};

#endif // RAY_H
