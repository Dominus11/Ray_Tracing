#ifndef CAMERA_H
#define CAMERA_H

#include <numeric>
#include "common.h"
#include "Primitives/hittable.h"
#include "Primitives/hittable_list.h"

class Camera {
    public:
        double aspect_ratio; // Ratio of img_width/img_height
        int16_t img_width;   // Rendered image width in pixels
        double focal_length; // Camera focal length - distance to viewport

    Camera(int16_t img_width, double aspect_ratio, double viewport_height, double f, const Point3& c):  
        img_width(img_width), 
        aspect_ratio(aspect_ratio), 
        focal_length(f),
        centre(c)
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
                Vec3 ray_dir = ul_pixel_centre + Vec3(i*du, - j*dv, 0.0) - centre;
                Ray r = Ray(centre, ray_dir);
                Color pixel_col = ray_color(r, scene);
                write_color(std::cout, pixel_col);
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


    Color ray_color(const Ray& r, const Hittable& scene) const{
        HitRecord rec = HitRecord();

        if (scene.hit(r, Interval(0, infinity), rec)){
            return 0.5*(rec.normal + Color(1,1,1));
        }

        Vec3 dir = unit(r.direction());
        auto a = 0.5*(dir.y() + 1.0);
        return (1.0-a)* Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
    }



};

#endif