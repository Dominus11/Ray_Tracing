#ifndef CAMERA_H
#define CAMERA_H

#include <numeric>
#include "common.h"
#include "Primitives/hittable.h"
#include "Primitives/hittable_list.h"
#include "Materials/material.h"

class Camera {
    public:
        double aspect_ratio; // Ratio of img_width/img_height
        int16_t img_width;   // Rendered image width in pixels
        double focal_length; // Camera focal length - distance to viewport
        int samps_per_pixel; // Number of samples taken for anti-aliasing per-pixel
        int max_depth;       // Maximum recursion depth for indirect illumination

    Camera(int16_t img_width, double aspect_ratio, double viewport_height, double f, const Point3& centre, int samples, int max_depth):  
        aspect_ratio(aspect_ratio), 
        img_width(img_width),
        focal_length(f),
        samps_per_pixel(samples),
        max_depth(max_depth),
        centre(centre)
    {
        img_height = int(img_width/aspect_ratio);
        img_height = (img_height < 1) ? 1: img_height;
        auto viewport_width = viewport_height * (double(img_width) / img_height);
        viewport_ul_corner = centre + Vec3(-viewport_width, viewport_height, 0)/2 - Vec3(0,0, focal_length);
        du = viewport_width/img_width;
        dv = viewport_height/img_height;
        ul_pixel_centre = viewport_ul_corner + Vec3(0.5*du, -0.5*dv, 0.0);

        std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";
    }

    void render(const Hittable& scene){
        for (int j = 0; j < img_height; j++){
            std::clog << "\rScanlines remaining: " << (img_height - j) << ' ' << std::flush ;


            for (int i = 0; i < img_width; i++){

                Color pixel_col(0,0,0);
                for (int n = 0; n < samps_per_pixel; n++){
                    Ray r = get_ray(i,j);
                    pixel_col += ray_color(r, max_depth, scene);
                }

                write_color(std::cout, pixel_col/samps_per_pixel);
            }
        }

        std::clog << "\rDone.                 \n";
    }
        

    private: 
        int16_t img_height;         // Rendered image height in pixels
        Point3 centre;              // Coordinates for the centre of the camera lens
        Point3 viewport_ul_corner;  // Coordinates for the upper-left corner of the viewport
        double du, dv;              // Step sizes bewteen connected pixels 
        Point3 ul_pixel_centre;     // Coordinates for the centre of the upper-left pixel on the viewport


    Color ray_color(const Ray& r, int depth, const Hittable& scene) const{
        HitRecord rec = HitRecord();

        if (depth <= 0){
            return Color(0,0,0);
        }

        // 0.001 prevents 'shadow acne', where a ray's intersection point may be slightly off the surface due to floating point errors, 
        // meaning that the reflected ray could re-intersect with the surface.
        if (scene.hit(r, Interval(0.001, infinity), rec)){
            Ray scattered;
            Color attenuation;

            if (rec.material->scatter(r, rec, attenuation, scattered)){
                return attenuation * ray_color(scattered, depth - 1, scene);
            }
            return Color(0,0,0);
        }

        Vec3 dir = unit(r.direction());
        auto a = 0.5*(dir.y() + 1.0);
        return (1.0-a)* Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
    }

    Ray get_ray(int i,int j) const{
        Vec3 offset = sample_pixel_offset();
        Vec3 ray_dir = ul_pixel_centre + Vec3((i+offset.x())*du, - (j+offset.y())*dv, 0.0) - centre;
        return Ray(centre, ray_dir);
    }

    Vec3 sample_pixel_offset() const{
        return Vec3(random_double()-0.5, random_double()-0.5, 0);
    }

};

#endif