/**vec3.hpp
* 
* 3D vector class.
*
*/

#ifndef VEC3_H
#define VEC3_H

class vec3 {
private:
    double e[3];
public:
    vec3();
    vec3(double e0, double e1, double e2);

    double x() const;
    double y() const;
    double z() const;

    vec3 operator-() const;
    double operator[](int i) const;
    double& operator[](int i);

    vec3& operator+=(const vec3& v);
    vec3& operator*=(double t);
    vec3& operator/=(double t);

    double length() const;
    double length_squared() const;
};

#endif // VEC3_H
