/**camera.cpp
*
* Camera class for:
* 1. constructing and dispatching rays.
* 2. rendering the final image.
*
*/

#include "constants.hpp"
#include "camera/camera.hpp"

Camera::Camera(int image_width, double aspect_ratio, double focal_length, double viewport_height)
    : image_width(image_width), aspect_ratio(aspect_ratio), viewport_height(viewport_height), focal_length(focal_length)
{
    this->init();
}

void Camera::init()
{
    // Image and viewport specs
    this->center = Point3(0, 0, 0);
    this->image_height = int(image_width / aspect_ratio);
    this->viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

    // Coordinate vectors and deltas
    auto viewport_u = Vec3(viewport_width, 0, 0);
    auto viewport_v = Vec3(0, -viewport_height, 0);
    this->pixel_delta_u = viewport_u / image_width;
    this->pixel_delta_v = viewport_v / image_height;

    // Upper left pixel: x = right, y = up, z = front
    // Since camera is in front of the viewport, -focal_length is on viewport
    // 0.5 delta displacement from upper left corner is the upper left pixel
    auto viewport_upper_left = center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    this->pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

Color Camera::ray_color(const Ray& r, const Hittable& world) const
{
    HitRecord rec;
    if (world.hit(r, Interval(0, +INF), rec))
        return 0.5 * (rec.normal + Color(1,1,1));
    
    // No hit
    Vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

void Camera::render(const Hittable& world)
{
    // P3 for ppm, width and height, max_val for RGB channels
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j)
    {
        std::clog << "\rLines pending for render: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) 
        {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - center;
            Ray r(center, ray_direction);

            Color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                      \n";
}

