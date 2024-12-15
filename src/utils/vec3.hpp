/**vec3.hpp
* 
* 3D vector class.
*
*/

#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include "constants.hpp"

class Vec3
{
private:
    double e[3];
public:
    Vec3();
    Vec3(double e0, double e1, double e2);

    double x() const;
    double y() const;
    double z() const;

    Vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    Vec3& operator+=(const Vec3& v);
    Vec3& operator*=(double t);
    Vec3& operator/=(double t);

    double length() const;
    double length_squared() const;

    static Vec3 random();
    static Vec3 random(double min, double max);

    bool near_zero(double epsilon = 0.8) const;
};

// Point class alias
using Point3 = Vec3;

// Vector Utility Functions
inline std::ostream& operator<<(std::ostream& out, const Vec3& v) { return out << v.x() << ' ' << v.y() << ' ' << v.z(); }

inline Vec3 operator+(const Vec3& u, const Vec3& v) { return Vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z()); }

inline Vec3 operator-(const Vec3& u, const Vec3& v) { return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z()); }

inline Vec3 operator*(const Vec3& u, const Vec3& v) { return Vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z()); }

inline Vec3 operator*(double t, const Vec3& v) { return Vec3(t * v.x(), t * v.y(), t * v.z()); }

inline Vec3 operator*(const Vec3& v, double t) { return t * v; }

inline Vec3 operator/(const Vec3& v, double t) { return (1/t) * v; }

inline double dot(const Vec3& u, const Vec3& v) { return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();}

inline Vec3 cross(const Vec3& u, const Vec3& v) 
{
    return Vec3(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x());
}

inline Vec3 unit_vector(const Vec3& v) { return v / v.length(); }

inline Vec3 random_unit_vector()
{
    // Rejection sampling
    while (true) {
        auto p = Vec3::random(-1, 1);
        auto lensq = p.length_squared();

        // Catch underflow and reject
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}

inline Vec3 random_in_unit_disk() {
    while (true) {
        auto p = Vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() < 1)
            return p;
    }
}

// inline Vec3 random_on_hemisphere(const Vec3& normal)
// {
//     Vec3 on_unit_sphere = random_unit_vector();
//     // In the same hemisphere as the normal
//     if (dot(on_unit_sphere, normal) > 0.0)
//         return on_unit_sphere;
//     else
//         return -on_unit_sphere;
// }

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2 * dot(v, n) * n;
}

inline Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    Vec3 r_out_perp =  etai_over_etat * (uv + cos_theta * n);
    Vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

#endif // VEC3_H
