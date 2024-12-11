/**camera.cpp
*
* Camera class for:
* 1. constructing and dispatching rays.
* 2. rendering the final image.
*
*/

#include <stdexcept>
#include "constants.hpp"
#include "camera/camera.hpp"

Camera::Camera()
    : image_width(-1), aspect_ratio(-1.0), viewport_height(-1.0), 
    focal_length(-1.0), camera_center(Point3(0, 0, 0)), samples_per_pixel(0) {}

// Setters
void Camera::set_image_width(int image_width)
{
    if (image_width < 1) throw std::domain_error("Camera: image_width should be at least 1.");
    this->image_width = image_width;
}

void Camera::set_aspect_ratio(double aspect_ratio)
{
    if (aspect_ratio <= 0) throw std::domain_error("Camera: aspect_ratio should be a positive real number.");
    this->aspect_ratio = aspect_ratio;
}

void Camera::set_viewport_height(double viewport_height)
{
    if (viewport_height <= 0) throw std::domain_error("Camera: viewport_height should be a positive real number.");
    this->viewport_height = viewport_height;
}

void Camera::set_focal_length(double focal_length)
{
    if (focal_length <= 0) throw std::domain_error("Camera: focal_length should be a positive real number.");
    this->focal_length = focal_length;
}

void Camera::set_camera_center(Point3 camera_center)
{
    this->camera_center = camera_center;
}

void Camera::set_samples_per_pixel(int samples_per_pixel)
{
    if (samples_per_pixel < 0) throw std::domain_error("Camera: samples_per_pixel should be a nonnegative integer.");
    this->samples_per_pixel = samples_per_pixel;
}

// Parameter check
bool Camera::check_params()
{
    bool image_width_given = image_width != -1;
    bool aspect_ratio_given = aspect_ratio != -1.0;
    bool viewport_height_given = viewport_height != -1.0;
    bool focal_length_given = focal_length != -1.0;
    
    return (image_width_given
            && aspect_ratio_given 
            && viewport_height_given
            && focal_length_given);
}

// Initialize camera
void Camera::init()
{
    // Check parameters
    if (!check_params()) throw std::out_of_range("Camera: Insufficient parameters.");

    // Image and viewport specs
    this->image_height = int(image_width / aspect_ratio);
    this->image_height = (this->image_height < 1) ? 1 : this->image_height;
    this->viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

    // Coordinate vectors and deltas
    auto viewport_u = Vec3(viewport_width, 0, 0);
    auto viewport_v = Vec3(0, -viewport_height, 0);
    this->pixel_delta_u = viewport_u / image_width;
    this->pixel_delta_v = viewport_v / image_height;

    // Upper left pixel: x = right, y = up, z = front
    // Since camera is in front of the viewport, -focal_length is on viewport
    // 0.5 delta displacement from upper left corner is the upper left pixel
    auto viewport_upper_left = camera_center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    this->pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Pixel sampling for antialiasing
    this->pixel_samples_scale = 1.0 / samples_per_pixel;
}

// Pixel sampling
Vec3 Camera::sample_square() const {
    return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

Ray Camera::get_ray(int i, int j) const {
    auto offset = sample_square();
    auto pixel_sample = pixel00_loc
                      + ((i + offset.x()) * pixel_delta_u)
                      + ((j + offset.y()) * pixel_delta_v);

    auto ray_origin = camera_center;
    auto ray_direction = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_direction);
}

// Ray coloring
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

// Render
void Camera::render(const Hittable& world)
{
    // Initialize parameters
    this->init();

    // P3 for ppm, width and height, max_val for RGB channels
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j)
    {
        std::clog << "\rLines pending for render: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) 
        {
            Color pixel_color(0, 0, 0);
            for (int sample = 0; sample < samples_per_pixel; sample++)
            {
                Ray r = get_ray(i, j);
                pixel_color += ray_color(r, world);
            }
            write_color(std::cout, pixel_samples_scale * pixel_color);
        }
    }
    std::clog << "\rDone.                      \n";
}

