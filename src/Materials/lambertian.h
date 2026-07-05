#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

class Lambertian : public Material {
    public:

        Lambertian(const Color& albedo): albedo(albedo) {}

        bool scatter(const Ray& r_in, HitRecord& record, Color& attenuation, Ray& scattered) const override final{
            auto scatter_dir = record.normal + random_unit_vector();

            // Catch degenerate scatter direction
            if (scatter_dir.near_zero()){
                scatter_dir = record.normal;
            }

            scattered = Ray(record.point, scatter_dir);
            attenuation = albedo;
            return true;
        }

    private:
        Color albedo;

};


#endif