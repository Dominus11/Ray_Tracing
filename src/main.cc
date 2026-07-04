#include "common.h"
#include "camera.h"
#include "Primitives/sphere.h"


int main(){
    // Camera Initialisation

    auto aspect_ratio = 16.0/9.0;
    int16_t img_width = 256; 
    auto viewport_height = 2.0;
    auto focal_length = 1.0; 
    Point3 camera_centre = Point3();
    int samples_per_pixel = 10;

    Camera camera = Camera(img_width, aspect_ratio, viewport_height, focal_length, camera_centre, samples_per_pixel);

    // Scene Initialisation

    HittableList scene = HittableList();
    scene.add(make_shared<Sphere>(Point3(0,0,-1), 0.5));
    scene.add(make_shared<Sphere>(Point3(0,-100.5,-1), 100));

    // Rendering

    camera.render(scene);

}