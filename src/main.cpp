/**main.cpp
*
* Main
*
*/

#include <iostream>

#include "elements/color.hpp"
#include "elements/ray.hpp"
#include "utils/vec3.hpp"

color ray_color(const Ray& r) {
    Vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
    // image specs
    auto aspect_ratio = 16.0 / 9.0;
    int image_height = 450;
    int image_width = int(image_height * aspect_ratio);

    // camera settings
    auto focal_length = 1.0;
    auto camera_center = Point3(0, 0, 0);
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    
    // pixel deltas
    auto viewport_u = Vec3(viewport_width, 0, 0);
    auto viewport_v = Vec3(0, -viewport_height, 0);
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Upper left pixel: x = right, y = up, z = front
    // Since camera is in front of the viewport, -focal_length is on viewport
    // 0.5 delta displacement from upper left corner is the upper left pixel
    auto viewport_upper_left = camera_center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // P3 for ppm, width and height, max_val for RGB channels
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j)
    {
        std::clog << "\rLines pending for render: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) 
        {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                      \n";
}

