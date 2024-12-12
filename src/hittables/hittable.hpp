/**hittable.hpp
*
* Abstraction for hittable objects.
*
*/

#ifndef HITTABLE_H
#define HITTABLE_H

#include <memory>
#include "elements/ray.hpp"
#include "utils/interval.hpp"

class Material; // Define later, resolves circular include

struct HitRecord
{
    Point3 p;
    Vec3 normal; // Outward unit normal
    std::shared_ptr<Material> mat;
    double t;
    bool front_face;
    
    // Determine side at geometry time by defining this->normal to always
    // point out of the surface. front_face = true if ray is incident
    // on surface from the outside.
    void set_face_normal(const Ray& r, const Vec3& outward_normal);
};

class Hittable
{
public:
    virtual bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
    virtual ~Hittable() = default; // Destructor set up
};

#endif // HITTABLE_H
