/**sphere.cpp
*
* Spherical objects.
*
*/

#include <cmath>
#include <stdexcept>

#include "hittables/sphere.hpp"

Sphere::Sphere(const Point3& center, double radius)
    : center(center)
{
    if (radius < 0) throw std::invalid_argument("Sphere: radius must be nonnegative");
    else this->radius = radius;
}

bool Sphere::hit(const Ray& r, Interval ray_t, HitRecord &rec) const
{
    // Find discriminant
    Vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = h * h - a * c;
    if (discriminant < 0)
        return false; // No hit

    auto sqrtd = std::sqrt(discriminant);

    // Check if hit is within accepted interval
    auto root = (h - sqrtd) / a;
    if (!ray_t.surrounds(root))
    {
        root = (h + sqrtd) / a;
        if (!ray_t.surrounds(root)) 
            return false;
    }

    // Store results in hit record struct
    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - center) / radius;

    return true;
}

