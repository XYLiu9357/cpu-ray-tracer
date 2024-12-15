/**camera.cpp
*
* Camera class for:
* 1. constructing and dispatching rays.
* 2. rendering the final image.
*
*/

#include <cmath>
#include <stdexcept>
#include "constants.hpp"
#include "camera/camera.hpp"

Camera::Camera()
    : image_width(-1), image_height(-1), aspect_ratio(-1.0), 
    viewport_width(-1.0), viewport_height(-1), vfov(90), 
    lookfrom(Point3(0, 0, 0)), lookat(Point3(0, 0, -1)), vup(Vec3(0, 1, 0)), 
    defocus_angle(-1.0), focus_dist(-1.0) , samples_per_pixel(100), max_depth(10) {}

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

void Camera::set_camera_orientation(Point3 lookfrom, Point3 lookat, Vec3 vup)
{
    this->lookfrom = lookfrom;
    this->lookat = lookat;
    this->vup = vup;
}

void Camera::set_defocus_blur(double defocus_angle, double focus_dist)
{
    this->defocus_angle = defocus_angle;
    this->focus_dist = focus_dist;
}

void Camera::set_vfov(double vfov)
{
    this->vfov = vfov;
}

void Camera::set_samples_per_pixel(int samples_per_pixel)
{
    if (samples_per_pixel <= 0) throw std::domain_error("Camera: samples_per_pixel should be a positive integer.");
    this->samples_per_pixel = samples_per_pixel;
}

void Camera::set_max_depth(int max_depth)
{
    if (max_depth <= 0) throw std::domain_error("Camera: max_depth should be a positive integer.");
    this->max_depth = max_depth;
}


// Parameter check
bool Camera::check_params()
{
    bool image_width_given = image_width != -1;
    bool aspect_ratio_given = aspect_ratio != -1.0;
    bool vfov_given = vfov != -1.0;
    bool defocus_blur_params_given = (defocus_angle != -1.0) && (focus_dist != -1.0);
    
    return (image_width_given
            && aspect_ratio_given
            && vfov_given
            && defocus_blur_params_given);
}

// Initialize camera
void Camera::init()
{
    // Check parameters
    if (!check_params()) throw std::out_of_range("Camera: Insufficient parameters.");

    // Image specs
    image_height = int(image_width / aspect_ratio);
    image_height = (this->image_height < 1) ? 1 : this->image_height;
    
    // Viewport specs
    auto theta = degrees_to_radians(vfov);
    auto h = std::tan(theta / 2);
    viewport_height = 2 * h * focus_dist;
    viewport_width = viewport_height * (double(image_width) / image_height);

    camera_center = lookfrom;

    // Camera basis vectors
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    // Viewport vectors
    Vec3 viewport_u = viewport_width * u;
    Vec3 viewport_v = (-1) * viewport_height * v;
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Upper left pixel: x = right, y = up, z = front
    auto viewport_upper_left = camera_center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
    this->pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Defocus disk basis
    auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;

    // Pixel sampling for antialiasing
    this->pixel_samples_scale = 1.0 / samples_per_pixel;
}

// Pixel sampling
Vec3 Camera::sample_square() const
{
    return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

Ray Camera::get_ray(int i, int j) const
{
    auto offset = sample_square();
    auto pixel_sample = pixel00_loc
                      + ((i + offset.x()) * pixel_delta_u)
                      + ((j + offset.y()) * pixel_delta_v);

    auto ray_origin = (defocus_angle <= 0) ? camera_center : defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_direction);
}


// Returns a random point in the camera defocus disk
Point3 Camera::defocus_disk_sample() const {
    auto p = random_in_unit_disk();
    return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}

// Ray coloring
Color Camera::ray_color(const Ray& r, int depth, const Hittable& world) const
{
    // End recursion if diffusion depth limit exceeded
    if (depth <= 0) return Color(0, 0, 0);

    HitRecord rec;

    // Hit
    if (world.hit(r, Interval(0.00001, +INF), rec))
    {
        Ray scattered;
        Color attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, depth - 1, world);
        return Color(0,0,0);
    }

    // No hit: render background
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
                pixel_color += ray_color(r, max_depth, world);
            }
            write_color(std::cout, pixel_samples_scale * pixel_color);
        }
    }
    std::clog << "\rDone.                      \n";
}

