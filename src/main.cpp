/**main.cpp
*
* Main
*
*/

#include <iostream>
#include <memory>

#include "camera/camera.hpp"
#include "elements/material.hpp"
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
    auto camera_center = Point3(0, 0, 0);
    
    // World
    HittableList world;
    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
    auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3( 0.0, 0.0, -1.2), 0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3( 1.0, 0.0, -1.0), 0.5, material_right));
    
    // Camera
    Camera cam;
    cam.set_image_width(image_width);
    cam.set_aspect_ratio(aspect_ratio);
    cam.set_viewport_height(viewport_height);
    cam.set_focal_length(focal_length);
    cam.set_camera_center(camera_center);
    cam.set_samples_per_pixel(100);
    cam.set_max_depth(10);
    cam.render(world);
}

