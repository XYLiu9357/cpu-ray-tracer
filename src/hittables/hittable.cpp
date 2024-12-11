/**hittable.hpp
*
* Abstraction for hittable objects.
*
*/

#include "hittables/hittable.hpp"
#include "utils/vec3.hpp"

void HitRecord::set_face_normal(const Ray& r, const Vec3& outward_normal)
{
    this->front_face = dot(r.direction(), outward_normal) < 0;
    this->normal = front_face ? outward_normal : -outward_normal;
}

