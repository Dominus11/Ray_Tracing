#include "vec3.h"
#include "color.h"
#include "ray.h"

#include <iostream>


double hit_sphere(const Point3& centre, double radius, const Ray& ray){
        auto a = dot(ray.direction(),ray.direction());
        auto h = dot((ray.origin() - centre), ray.direction());
        auto c = (ray.origin() - centre).length_squared() - radius * radius;
        auto D = h*h - a*c;

        if (D < 0){
            return -1.0;
        } else {
            return (-h - std::sqrt(D))/a;
        }
}

Color ray_color(const Ray& r){
    auto t = hit_sphere(Point3(0,0,-1), 0.5, r);

    if (t > 0.0){
        Vec3 N = unit(r.at(t) - Vec3(0,0,-1));
        return 0.5*Color(N.x()+1, N.y()+1, N.z()+1);
    }


    Vec3 dir = unit(r.direction());
    auto a = 0.5*(dir.y() + 1.0);
    // std::cout << a << '\n';
    //exit(0);
    return (1.0-a)* Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
}


int main(){

    // Image

    auto aspect_ratio = 16.0/9.0;
    int16_t img_width = 256; 
    int16_t img_height = int(img_width/aspect_ratio);
    img_height = (img_height < 1) ? 1: img_height;

    // Camera + Viewport

    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(img_width) / img_height);   
    auto focal_length = 1.0; 

    Point3 camera_centre = Point3();
    Point3 viewport_ul_corner = camera_centre + Vec3(-viewport_width, viewport_height, 0)/2 - Vec3(0,0, focal_length);
    double du = viewport_width/img_width;
    double dv = viewport_height/img_height;
    Point3 ul_pixel_centre = viewport_ul_corner + Vec3(0.5*du, -0.5*dv, 0.0); 
    
    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    // Rendering

    for (int j = 0; j < img_height; j++){
        std::clog << "\rScanlines remaining: " << (img_height - j) << ' ' << std::flush ;
        for (int i = 0; i < img_width; i++){
            Vec3 ray_dir = ul_pixel_centre + Vec3(i*du, - j*dv, 0.0) - camera_centre;
            Ray r = Ray(camera_centre, ray_dir);
            Color pixel_col = ray_color(r);
            write_color(std::cout, pixel_col);
        }
    }

    std::clog << "\rDone.                 \n";

}