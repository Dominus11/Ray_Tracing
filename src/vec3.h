#ifndef VEC3_H
#define VEC3_H

#include "common.h"

class Vec3 {
    double e[3];

    public:
        Vec3() : e{0,0,0} {}
        Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}
        Vec3(const Vec3& v): e{v.e[0], v.e[1], v.e[2]} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    Vec3 operator-() const {return Vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i){return e[i];}

    Vec3& operator=(Vec3 v){
        e[0] = v[0];
        e[1] = v[1];
        e[2] = v[2];
        return *this;
    }

    Vec3& operator+=(Vec3 v){
        e[0] += v[0];
        e[1] += v[1];
        e[2] += v[2];
        return *this;
    }

    Vec3& operator*=(double s){
        e[0] *= s;
        e[1] *= s;
        e[2] *= s;
        return *this;
    }

    double length_squared(){
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    double length(){
        return std::sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }

    static Vec3 random_vec(){
        return Vec3(random_double(), random_double(), random_double());
    }

    static Vec3 random_vec(double min, double max){
        return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

};

using Point3 = Vec3;

// Vector Utilities

// Arithmetic

inline Vec3 operator+(Vec3 v1, Vec3 v2){
    return Vec3(v1[0] + v2[0], v1[1]+v2[1], v1[2] + v2[2]);
}

inline Vec3 operator-(Vec3 v1, Vec3 v2){
    return Vec3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

/*inline Vec3 operator-(Vec3 v) {
    return Vec3(-v[0], -v[1], -v[2]);
}*/

/* Is this one even useful??
inline vec3 operator*(vec3 v1, vec3 v2){
    return vec3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
} */

inline Vec3 operator*(double t, Vec3 v){
    return Vec3(t*v[0], t*v[1], t*v[2]);
}

inline Vec3 operator*(Vec3 v, double t){
    return t * v;
}

/* Is this useful either? 
inline vec3 operator/(vec3 v1, vec3 v2){
    return vec3(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
} */

inline Vec3 operator/(Vec3 v, double t){
    return v * (1/t);
}

// Geometric

inline double dot(Vec3 v1, Vec3 v2){
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

inline double angle(Vec3 v1, Vec3 v2){
    return dot(v1, v2)/(v1.length() * v2.length());
}

inline Vec3 cross (Vec3 v1, Vec3 v2){
    return Vec3(v1[1] * v2[2] - v2[1] * v1[2], v1[2] * v2[0] - v1[0] * v2[2], v1[0] * v2[1] - v2[0] * v1[1]);
}

inline Vec3 unit(Vec3 v){
    return v / v.length();
}

inline Vec3 random_unit_vector() {

    // Rejection sampling used bc it's
    // faster than deterministic method on average 
    // bc sin, cos take loads of operations

    while (true) {
        auto p = Vec3::random_vec(-1,1);
        auto lensq = p.length_squared();
        // 1e-160 check to avoid normalisations blowing up to ±infty
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}

inline Vec3 random_on_hemisphere(const Vec3& normal){
    Vec3 on_sphere = random_unit_vector();

    if (dot(on_sphere, normal) > 0.0){
        return on_sphere;
    } else {
        return -on_sphere;
    }
}

#endif