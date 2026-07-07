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
        int samps_per_pixel; // Number of samples taken for anti-aliasing per-pixel
        int max_depth;       // Maximum recursion depth for indirect illumination
        double vfov;         // The vertical viewing angle
        Point3 lookfrom;     // Viewport centre, point camera is looking from
        Point3 lookat;       // Point camera is looking at
        Vec3 vup;            // 'Up' direction in camera frame
        double defocus_angle;
        double focus_dist;

    void initialise(){

        // Image details
        img_height = int(img_width/aspect_ratio);
        img_height = (img_height < 1) ? 1: img_height;


        // Viewport dimensions
        auto theta = degrees_to_radians(vfov);
        auto h = std::tan(theta/2);
        auto viewport_height = 2*h*focus_dist;
        auto viewport_width = viewport_height * (double(img_width) / img_height);

        // Camera frame of reference
        centre = lookfrom;
        w = - unit(lookat - lookfrom);
        u = unit(cross(vup,w));
        v = cross(w,u);

        // Defocus Disk Dimensions
        auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle)/2);
        lens_u = u*defocus_radius;
        lens_v = v*defocus_radius;

        // Viewport coordinates
        Vec3 view_u = viewport_width * u;
        Vec3 view_v = viewport_height * -v;
        viewport_ul_corner = centre - (focus_dist*w) - (view_u + view_v)/2; 

        // Subdivision into pixels
        du = view_u/img_width;
        dv = view_v/img_height;
        ul_pixel_centre = viewport_ul_corner + (du+dv)/2;

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
        Vec3 u,v,w;                 // Basis vectors in the camera's reference frame
        Vec3 du, dv;                // Steps bewteen connected pixels 
        Point3 ul_pixel_centre;     // Coordinates for the centre of the upper-left pixel on the viewport
        Vec3 lens_u, lens_v;        // Vectors indicating horizontal, vertical semi-axes of lens


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
        Vec3 pix_sample = ul_pixel_centre + + (i+offset.x())*du + (j+offset.y())*dv;
        Vec3 lens_point = (defocus_angle <= 0) ? centre : sample_defocus_disk();
        Vec3 ray_dir = pix_sample - lens_point;
        return Ray(lens_point, ray_dir);
    }

    Vec3 sample_pixel_offset() const{
        return Vec3(random_double()-0.5, random_double()-0.5, 0);
    }

    Point3 sample_defocus_disk() const {
        auto p = random_on_unit_disk();
        return centre + p.x()*lens_u + p.y()*lens_v;
    }

};

#endif