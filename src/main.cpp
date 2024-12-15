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
    auto camera_center = Point3(0, 0, 0);
    
    // World
    HittableList world;
    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left   = std::make_shared<Dielectric>(1.50);
    auto material_bubble = std::make_shared<Dielectric>(1.00 / 1.50);
    auto material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.4, material_bubble));
    world.add(std::make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right));
    
    // Camera
    Camera cam;
    cam.set_image_width(image_width);
    cam.set_aspect_ratio(aspect_ratio);
    cam.set_samples_per_pixel(100);
    cam.set_max_depth(50);
    cam.set_vfov(20);
    cam.set_camera_orientation(Point3(-2, 2, 1), Point3(0, 0, -1), Vec3(0, 1, 0));
    cam.render(world);
}

