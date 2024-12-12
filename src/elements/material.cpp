/**material.hpp
*
* Abstract class for materials
*
*/


#include "elements/material.hpp"
#include "utils/vec3.hpp"

// Perfect lambertian
Lambertian::Lambertian(const Color& albedo) : albedo(albedo) {}
bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
    auto scatter_direction = rec.normal + random_unit_vector();

    // Catch degenerate scatter direction
    if (scatter_direction.near_zero())
        scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

// Metal
Metal::Metal(const Color& albedo, double fuzz) : albedo(albedo)
{
    if (fuzz < 0) throw std::domain_error("Metal: fuzz should be a nonnegative real number.");
    this->fuzz = fuzz;
}
bool Metal::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
    Vec3 reflected = reflect(r_in.direction(), rec.normal);
    reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
    scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

