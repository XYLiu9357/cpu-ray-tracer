/**material.hpp
*
* Abstract class for materials
*
*/

#include "constants.hpp"
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

// Dielectric
Dielectric::Dielectric(double refraction_index) : refraction_index(refraction_index) {}

// Use Schlick's approximation for reflectance.
double Dielectric::reflectance(double cosine, double refraction_index)
{
    auto r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}

bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
    attenuation = Color(1.0, 1.0, 1.0);
    double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

    Vec3 unit_direction = unit_vector(r_in.direction());

    // Check if refraction is possible
    double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);
    bool cannot_refract = ri * sin_theta > 1.0;
    Vec3 direction;

    if (cannot_refract || reflectance(cos_theta, ri) > random_double()) // Total internal reflection
        direction = reflect(unit_direction, rec.normal);
    else // Refraction
        direction = refract(unit_direction, rec.normal, ri);

    scattered = Ray(rec.p, direction);
    return true;
}

