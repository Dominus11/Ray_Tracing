#ifndef METAL_H
#define METAL_H

#include "material.h"

class Metal : public Material {
    public:
        Metal(const Color& albedo, double fuzz): albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

        bool scatter(const Ray& r_in, HitRecord& record, Color& attenuation, Ray& scattered) const override final{
            Vec3 reflected = reflect(r_in.direction(), record.normal);
            Vec3 scattered_dir = unit(reflected) + fuzz * random_unit_vector();
            scattered = Ray(record.point, scattered_dir);
            attenuation = albedo;
            return dot(record.normal, scattered_dir) > 0.0;
        }

    private:
         Color albedo;
         double fuzz;
};

#endif