#include "common.h"
#include "./Primitives/sphere.h"
#include "./Primitives/hittable_list.h"

Color ray_color(const Ray& r, const Hittable& scene){
    HitRecord rec = HitRecord();

    if (scene.hit(r, Interval(0, infinity), rec)){
        return 0.5*(rec.normal + Color(1,1,1));
    }

    Vec3 dir = unit(r.direction());
    auto a = 0.5*(dir.y() + 1.0);
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

    // Scene Generation

    
    HittableList scene = HittableList();

    scene.add(make_shared<Sphere>(Point3(0,0,-1), 0.5));
    scene.add(make_shared<Sphere>(Point3(0,-100.5,-1), 100));

    // Rendering

    for (int j = 0; j < img_height; j++){
        std::clog << "\rScanlines remaining: " << (img_height - j) << ' ' << std::flush ;
        for (int i = 0; i < img_width; i++){
            Vec3 ray_dir = ul_pixel_centre + Vec3(i*du, - j*dv, 0.0) - camera_centre;
            Ray r = Ray(camera_centre, ray_dir);
            Color pixel_col = ray_color(r, scene);
            write_color(std::cout, pixel_col);
        }
    }

    std::clog << "\rDone.                 \n";

}