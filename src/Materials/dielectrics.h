#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"

class Dielectric : public Material{
    public:

        Dielectric(double n) : refractive_index(n) {}

        bool scatter(const Ray& r_in, HitRecord& record, Color& attenuation, Ray& r_out) const override final {
            Vec3 scattered_dir;
            double ri = record.front_face ? 1/refractive_index : refractive_index;
            attenuation = Color(1.0, 1.0, 1.0);

            Vec3 unit_direction = unit(r_in.direction());
            auto cos_theta = std::fmin(dot(-unit_direction, record.normal), 1.0);
            auto sin_theta = std::sqrt(1- cos_theta * cos_theta);

            if (ri * sin_theta > 1.0 || reflectance(cos_theta, ri) > random_double()){
                scattered_dir = reflect(unit_direction, record.normal);
            } else{
                scattered_dir = refract(unit_direction, record.normal, ri);
            }

            r_out = Ray(record.point, scattered_dir);
            
            return true;
        }

    private:
        double refractive_index;

        static double reflectance(double cosine, double refraction_index) {
            // Use Schlick's approximation for reflectance.
            auto r0 = (1 - refraction_index) / (1 + refraction_index);
            r0 = r0*r0;
            return r0 + (1-r0)*std::pow((1 - cosine),5);
        }

};


#endif