/**main.cpp
*
* Main
*
*/

#include <iostream>
#include <memory>

#include "camera/camera.hpp"
#include "elements/color.hpp"
#include "elements/material.hpp"
#include "hittables/hittable.hpp"
#include "hittables/hittable-list.hpp"
#include "hittables/sphere.hpp"
#include "utils/vec3.hpp"
#include "utils/worldgen.hpp"
#include "utils/io.hpp"

int main() {
    // Image specs
    int image_width = 400;
    auto aspect_ratio = 16.0 / 9.0;
    auto camera_center = Point3(0, 0, 0);
    
    // World
    HittableList world = get_world_many_spheres();
        
    // Camera
    Camera cam;
    cam.set_aspect_ratio(aspect_ratio);
    cam.set_image_width(image_width);
    cam.set_samples_per_pixel(20);
    cam.set_max_depth(10);
    cam.set_vfov(20);
    cam.set_camera_orientation(Point3(13, 2, 3), Point3(0, 0, 0), Vec3(0, 1, 0));
    cam.set_defocus_blur(0.6, 10.0);
    
    std::vector<std::vector<Color>> img_arr;
    cam.render(world, img_arr);
    write_ppm(std::cout, img_arr);
}

