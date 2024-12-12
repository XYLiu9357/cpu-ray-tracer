/**sphere.cpp
*
* Spherical objects.
*
*/

#include <cmath>
#include <memory>
#include <stdexcept>

#include "hittables/sphere.hpp"

Sphere::Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat)
{
    if (radius < 0) throw std::invalid_argument("Sphere: radius must be nonnegative");
    this->center = center;
    this->radius = radius;
    this->mat = mat;
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
    rec.mat = mat;
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}

