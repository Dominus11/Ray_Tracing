#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class Sphere: public Hittable {
    public:

        Sphere(const Point3& static_centre, const double r, shared_ptr<Material> mat): centre(static_centre, Vec3(0,0,0)), radius(std::fmax(0, r)), material(mat) {}
        Sphere(const Point3& c1, const Point3&c2, const double r, shared_ptr<Material> mat): centre(c1, c2 - c1), radius(std::fmax(0,r)), material(mat) {}

        virtual bool hit(const Ray& ray, Interval ray_t, HitRecord& record) const override{
            auto a = dot(ray.direction(),ray.direction());
            auto centre_pos = centre.at(ray.time());
            auto h = dot((ray.origin() - centre_pos), ray.direction());
            auto c = (ray.origin() - centre_pos).length_squared() - radius * radius;
            auto D = h*h - a*c;

            if (D < 0){ return false; }

            auto sqrtD = std::sqrt(D);
            auto t = (-h - sqrtD)/a;

            // If you're just short of the interval, you might want to
            // try the further root to see if you land inside
            if (!ray_t.surrounds(t)){
                t = (-h + sqrtD)/a;
                if (!ray_t.surrounds(t)){
                    return false;
                }
            }

            record.t = t;
            record.point = ray.at(t);
            Vec3 outward_normal = (record.point - centre_pos)/radius;
            record.set_face_normal(ray, outward_normal);
            record.material = material;
            
            return true;
        }

    private:
        Ray centre;
        double radius;
        shared_ptr<Material> material;

};


#endif