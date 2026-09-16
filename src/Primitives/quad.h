#ifndef QUAD_H
#define QUAD_H

#include "hittable.h"

class Quad : public Hittable{
    public:
        Quad(const Point3& corner, const Vec3& u, const Vec3& v, shared_ptr<Material> mat): 
            corner(corner), u(u), v(v), n_out(cross(u, v)), 
            w(n_out / dot(n_out,n_out)), D(dot(corner, n_out)), material(mat) {}
    
        virtual bool hit(const Ray& ray, Interval ray_t, HitRecord& record) const override{
            double denom = dot(ray.direction(), n_out);
            
            if ( std::fabs(denom) < 1e-8){ return false; }

            double t = (D -dot(ray.origin(), n_out))/denom;

            if (!ray_t.contains(t)){return false;}

            Vec3 intersection = ray.at(t);
            Vec3 p = intersection - corner;
            double alpha = dot(w, cross(p, v));
            double beta = dot(w, cross(u, p));

            if(!within_quad(alpha, beta)){return false;}

            record.material = material;
            record.set_face_normal(ray, unit(n_out));
            record.t = t;
            record.point = intersection;

            return true;

        }

        virtual bool within_quad(double alpha, double beta) const {
            Interval unit = Interval(0,1);

            if (!unit.contains(alpha) || !unit.contains(beta)){ return false; }

            return true;
        }
        


    private:
        Point3 corner;
        Vec3 u, v, n_out, w;
        double D;
        shared_ptr<Material> material;

};


#endif
