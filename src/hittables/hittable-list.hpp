/**hittable-list.hpp
*
* A collection of hittable objects.
*
*/

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "elements/ray.hpp"
#include "hittables/hittable.hpp"
#include "utils/interval.hpp"

class HittableList : public Hittable
{
private:
    std::vector<std::shared_ptr<Hittable>> objects;
    
public:
    HittableList();
    HittableList(std::shared_ptr<Hittable> object);

    void clear();
    void add(std::shared_ptr<Hittable> object);

    bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override;
};

#endif // HITTABLE_LIST_H

