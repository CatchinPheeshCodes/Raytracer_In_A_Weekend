#ifndef VEC3_H
#define VEC3_H

#include "rtweekend.h"
//vec3 class is for storing 3D geometric vectors and colors. 
class vec3 {
    public:
        double e[3];

        //initialize array.
        vec3() : e{0, 0, 0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        //functions to access x, y, and z coordinates.
        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        //overload unary minus operator. returns new vec3 object with all components negated.
        vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]); }
        //overload subscript operator. returns i-th element of e array. Does not allow for modification.
        double operator[](int i) const { return e[i]; }
        //overloads subscript operator. Allows modification of i-th element of e array.
        double& operator[](int i) {return e[i]; }

        //overloads += operator. adds components of another vec3 object to primary object.
        vec3& operator+=(const vec3& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        //overloads *= operator.  multiplies components of vec3 object by a scalar.
        vec3& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        //overloads /= operator. Divides components of vec3 object by a scalar.
        vec3& operator/=(double t) {
            return *this *= 1/t;
        }

        //Computes the actual length of the vector.
        double length() const {
            return std::sqrt(length_squared());
        }
        //Computes the squared length of the vector. 
        double length_squared () const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
        //Returns true if vector is close to 0 in all dims.  Prevents zero scatter direction vector.
        bool near_zero() const {
            auto s = 1e-8;
            return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
        }
        //generates an arbitrary vector.
        static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }
        //generates an arbitrary vector with bounds.
        static vec3 random(double min, double max) {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }
};

//declaring point3 as an alias for vec3. Used when operating on a point.
using point3 = vec3;

//Vector utility functions.

//overloads << operator. vec3 objects can be printed to an output stream.
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
//overloads + operator. adds components of two vec3 objects together.
inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
//overloads - operator. subtracts components of first vec3 objects from second.
inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2]-v.e[2]);
}
//overloads * operator. multiplies components of two vec3 objects.
inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
//overloads * operator. multiplies components of vector by a scalar.
inline vec3 operator*(double t, const vec3& v) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}
inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}
//overloads / operator. divides components of vector by scalar.
inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}
//calculates the dot product of two vectors.
inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}
//calculates the cross product of two vectors.
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1], 
                u.e[2] * v.e[0] - u.e[0] * v.e[2], 
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
//returns the unit vector of a vector.
inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}
inline vec3 random_unit_vector() {
    while(true) {
        auto p = vec3::random(-1, 1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1) {
            return p / sqrt(lensq);
        }
    }
}
inline vec3 random_on_hemisphere(const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if(dot(on_unit_sphere, normal) > 0.0) {
        return on_unit_sphere;
    }
    else {
        return -on_unit_sphere;
    }
}
inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}
inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

#endif