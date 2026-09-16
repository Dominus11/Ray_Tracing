#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Primitives/hittable.h"

class Material {
    public:
        virtual ~Material() = default;
        virtual bool scatter(const Ray& r_in, HitRecord& record, Color& attenuation, Ray& r_out) const = 0;

};

#include "lambertian.h"
#include "metal.h"
#include "dielectrics.h"

#endif