/**sphere.hpp
*
* Spherical objects.
*
*/

#ifndef SPHERE_H
#define SPHERE_H

#include "hittables/hittable.hpp"
#include "utils/interval.hpp"
#include "utils/vec3.hpp"

class Sphere : public Hittable
{
private:
    Point3 center;
    double radius;

public:
    Sphere(const Point3& center, double radius);
    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;
};

#endif // SPHERE_H

