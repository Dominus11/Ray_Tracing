#ifndef HITTABLE_H
#define HITTABLE_H

#include "../common.h"

class HitRecord {
    public:
        Point3 point;
        Vec3 normal;
        double t = -1.0;
        bool front_face;

        void set_face_normal(const Ray& r, const Vec3& outward_normal) {
            // Sets the hit record normal vector.
            // NOTE: the parameter `outward_normal` is assumed to have unit length.

            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
};


class Hittable {
    public:
        virtual ~Hittable() = default;
        virtual bool hit(const Ray &ray, Interval ray_t, HitRecord& record) const = 0;
};


#endif