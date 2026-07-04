#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class Sphere: public Hittable {
    public:
        

        Sphere(const Point3& a, const double r): centre(a), radius(std::fmax(0, r)) {}

        virtual bool hit(const Ray& ray, Interval ray_t, HitRecord& record) const override{
            auto a = dot(ray.direction(),ray.direction());
            auto h = dot((ray.origin() - centre), ray.direction());
            auto c = (ray.origin() - centre).length_squared() - radius * radius;
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
            Vec3 outward_normal = (record.point - centre)/radius;
            record.set_face_normal(ray, outward_normal);
            
            
            return true;
        }

    private:
        Point3 centre;
        double radius;

};


#endif