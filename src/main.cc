#include "common.h"
#include "camera.h"
#include "Primitives/sphere.h"
#include "Materials/material.h"


int main(){
    // Camera Initialisation

    auto aspect_ratio = 16.0/9.0;
    int16_t img_width = 400; 
    auto viewport_height = 2.0;
    auto focal_length = 1.0; 
    Point3 camera_centre = Point3();
    int samples_per_pixel = 100;
    int max_depth = 50;

    Camera camera = Camera(img_width, aspect_ratio, viewport_height, focal_length, camera_centre, samples_per_pixel, max_depth);

    // Scene Initialisation

    HittableList scene = HittableList();

    auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
    auto material_right  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    scene.add(make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    scene.add(make_shared<Sphere>(Point3( 0.0,    0.0, -1.2),   0.5, material_center));
    scene.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
    scene.add(make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right));


    // Rendering

    camera.render(scene);

}