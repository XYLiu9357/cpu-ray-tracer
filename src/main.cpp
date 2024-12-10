/**main.cpp
*
* Main
*
*/

#include <iostream>
#include <memory>

#include "camera/camera.hpp"
#include "hittables/hittable.hpp"
#include "hittables/hittable-list.hpp"
#include "hittables/sphere.hpp"
#include "utils/vec3.hpp"

int main() {
    // image specs
    int image_width = 800;
    auto aspect_ratio = 16.0 / 9.0;
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    
    // World
    HittableList world;
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));
    
    // Camera
    Camera cam (image_width, aspect_ratio, focal_length, viewport_height);
    cam.render(world);
}

