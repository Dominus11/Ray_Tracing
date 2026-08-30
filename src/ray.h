#ifndef RAY_H
#define RAY_H

#include "common.h"


class Ray {
    public:

        Ray() {}
        Ray(const Point3& o, const Vec3& t, double time) : orig(o), dirn(t), tm(time) {}
        Ray(const Point3& o, const Vec3& t) : orig(o), dirn(t), tm(0) {}

        const Point3& origin()  const  { return orig; }
        const Vec3&   direction() const { return dirn; }

        double time() const{ return tm; }

        Point3 at(double t) const{
            return orig + t * dirn;
        }
    
    private:
        Point3 orig;
        Vec3 dirn;
        double tm;

};


#endif