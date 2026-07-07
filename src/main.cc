#include "common.h"
#include "camera.h"
#include "Primitives/sphere.h"
#include "Materials/material.h"


int main(){
    // Camera Initialisation

    Camera camera;

    camera.aspect_ratio = 16.0/9.0;
    camera.img_width = 400;
    camera.samps_per_pixel = 100;
    camera.max_depth = 50;
    
    camera.vfov = 20;
    camera.lookfrom = Point3(-2,2,1);
    camera.lookat = Point3(0,0,-1);
    camera.vup = Vec3(0,1,0);

    camera.defocus_angle = 10.0;
    camera.focus_dist = 3.4;

    camera.initialise();

    // Scene Initialisation

    HittableList scene = HittableList();

    /*
    auto R = std::cos(pi/4);

    auto material_left  = make_shared<Lambertian>(Color(0,0,1));
    auto material_right = make_shared<Lambertian>(Color(1,0,0));

    scene.add(make_shared<Sphere>(Point3(-R, 0, -1), R, material_left));
    scene.add(make_shared<Sphere>(Point3( R, 0, -1), R, material_right));
    */

    auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Dielectric>(1.50);
    auto material_bubble = make_shared<Dielectric>(1.00 / 1.50);
    auto material_right  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    scene.add(make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    scene.add(make_shared<Sphere>(Point3( 0.0,    0.0, -1.2),   0.5, material_center));
    scene.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
    scene.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.4, material_bubble));
    scene.add(make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right));


    // Rendering

    camera.render(scene);

}