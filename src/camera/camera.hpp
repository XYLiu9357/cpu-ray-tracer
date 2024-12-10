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
#include "hittables/hittable.hpp"
#include "utils/vec3.hpp"

class Camera {
private:
    int image_width, image_height;
    double aspect_ratio;
    double viewport_width, viewport_height;

    double focal_length;
    Point3 center; 
    Vec3 pixel_delta_u, pixel_delta_v;
    Point3 pixel00_loc;
    
    // Initialize camera based on provided specs
    void init();

    // Construct rays
    Color ray_color(const Ray& r, const Hittable& world) const;

public:
    // Constructor: calls init()
    Camera(int image_width, double aspect_ratio, double focal_length = 1.0, double viewport_height = 2.0);

    // Render image and output to stdout
    void render(const Hittable& world);
};

#endif
