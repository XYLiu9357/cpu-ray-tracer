/**sphere.hpp
*
* Spherical objects.
*
*/

#ifndef SPHERE_H
#define SPHERE_H

#include <memory>
#include "hittables/hittable.hpp"
#include "elements/material.hpp"
#include "utils/interval.hpp"
#include "utils/vec3.hpp"

class Sphere : public Hittable
{
private:
    Point3 center;
    double radius;
    std::shared_ptr<Material> mat;

public:
    Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat);
    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;
};

#endif // SPHERE_H

