/**ray.hpp
* 
* Ray class.
*
*/

#ifndef RAY_H
#define RAY_H

#include "elements/point3.hpp"
#include "utils/vec3.hpp"

class ray {
private:
    point3 orig;
    vec3 dir;

public:
    ray();
    ray(const point3& origin, const vec3& direction);
    const point3& origin() const;
    const vec3& direction() const;
    point3 at(double t) const;
};

#endif // RAY_H
