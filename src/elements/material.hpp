/**material.hpp
*
* Abstract class for materials
*
*/

#ifndef MATERIAL_H
#define MATERIAL_H

#include "elements/ray.hpp"
#include "elements/color.hpp"
#include "hittables/hittable.hpp"

class Material 
{
public:
    virtual ~Material() = default;
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, 
                         Color& attenuation, Ray& scattered) const { return false; }
};

class Lambertian : public Material
{
private:
    Color albedo;

public:
    Lambertian(const Color& albedo);
    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;
};

class Metal : public Material {
private:
    Color albedo;
    double fuzz;

public:
    Metal(const Color& albedo, double fuzz);
    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;
};

class Dielectric : public Material
{
private:
    double refraction_index;
    static double reflectance(double cosine, double refraction_index);

public:
    Dielectric(double refraction_index);
    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;
};

#endif // MATERIAL_H
