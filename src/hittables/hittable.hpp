/**hittable.hpp
*
* Abstraction for hittable objects.
*
*/

#ifndef HITTABLE_H
#define HITTABLE_H

#include "elements/ray.hpp"
#include "utils/interval.hpp"

struct HitRecord
{
    Point3 p;
    Vec3 normal; // Outward unit normal
    double t;
};

class Hittable
{
public:
    virtual bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
    virtual ~Hittable() = default; // Destructor set up
};

#endif // HITTABLE_H
