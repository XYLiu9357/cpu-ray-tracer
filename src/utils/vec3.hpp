/**vec3.hpp
* 
* 3D vector class.
*
*/

#ifndef VEC3_H
#define VEC3_H

#include <iostream>

class Vec3 {
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

#endif // VEC3_H
