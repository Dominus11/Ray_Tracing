#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"

class Triangle : public Hittable{

    public:
    // Accepts vertices in anticlockwise order, starting from bottom-leftmost corner
    Triangle(Point3 v1, Point3 v2, Point3 v3, shared_ptr<Material> mat): 
        c(v1), u(v2-v1), v(v3-v1), n(cross(u,v)), 
        w(n / dot(n, n)), D(dot(v1, n)),mat(mat) {}

    virtual bool hit(const Ray& ray, Interval ray_t, HitRecord& record) const override{
        double denom = dot(ray.direction(), n);
            
        if ( std::fabs(denom) < 1e-8){ return false; }

        double t = (D -dot(ray.origin(), n))/denom;

        if (!ray_t.contains(t)){return false;}

        Vec3 intersection = ray.at(t);
            Vec3 p = intersection - c;
            double alpha = dot(w, cross(p, v));
            double beta = dot(w, cross(u, p));

            if(!within_triangle(alpha, beta)){return false;}

            record.material = mat;
            record.set_face_normal(ray, unit(n));
            record.t = t;
            record.point = intersection;

            return true;
    }

    virtual bool within_triangle(double alpha, double beta) const {
            return !(alpha < 0 || beta < 0 || alpha + beta > 1);
    }


    private:
        Point3 c;
        Vec3 u,v, n, w;
        double D;
        shared_ptr<Material> mat;
};




#endif