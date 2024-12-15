/**camera.hpp
*
* Camera class for:
* 1. constructing and dispatching rays.
* 2. rendering the final image.
*
*/

#ifndef CAMERA_H
#define CAMERA_H

#include "elements/color.hpp"
#include "elements/ray.hpp"
#include "elements/material.hpp"
#include "hittables/hittable.hpp"
#include "utils/vec3.hpp"

class Camera {
private:
    // Image, viewport, and camera
    int image_width, image_height;
    double aspect_ratio;
    double viewport_width, viewport_height;
    double focal_length;
    Vec3 pixel_delta_u, pixel_delta_v;
    Point3 pixel00_loc;
    
    // Camera orientation
    Point3 camera_center;
    Point3 lookfrom;
    Point3 lookat;
    Vec3 vup;
    Vec3 u, v, w;

    // Antialiasing
    int samples_per_pixel;
    double pixel_samples_scale;

    // Diffusion
    int max_depth;

    // Positionable camera
    double vfov;
    
    // Check if the parameters given are valid
    bool check_params();
    
    // Initialize camera based on provided specs
    void init();

    // Pixel sampling
    Vec3 sample_square() const; // [-0.5, 0.5] * [-0.5, 0.5] square sample
    Ray get_ray(int i, int j) const; // Ray from origin to sampled point
    
    // Ray attributes
    Color ray_color(const Ray& r, int depth, const Hittable& world) const;

public:
    // Constructor
    Camera();

    // Mutators
    void set_image_width(int image_width);
    void set_aspect_ratio(double aspect_ratio);
    void set_camera_orientation(Point3 lookfrom, Point3 lookat, Vec3 vup);
    void set_vfov(double vfov);
    void set_samples_per_pixel(int samples_per_pixel);
    void set_max_depth(int max_depth);

    // Render image and output to stdout
    void render(const Hittable& world);
};

#endif
