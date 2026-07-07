#include "common.h"
#include "camera.h"
#include "Primitives/sphere.h"
#include "Materials/material.h"


int main(){
    // Camera Initialisation

    Camera camera;

    camera.aspect_ratio = 16.0/9.0;
    camera.img_width = 1200;
    camera.samps_per_pixel = 500;
    camera.max_depth = 50;
    
    camera.vfov = 20;
    camera.lookfrom = Point3(13,2,3);
    camera.lookat = Point3(0,0,0);
    camera.vup = Vec3(0,1,0);

    camera.defocus_angle = 0.6;
    camera.focus_dist = 10.0;

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

    /* auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Dielectric>(1.50);
    auto material_bubble = make_shared<Dielectric>(1.00 / 1.50);
    auto material_right  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    scene.add(make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    scene.add(make_shared<Sphere>(Point3( 0.0,    0.0, -1.2),   0.5, material_center));
    scene.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
    scene.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.4, material_bubble));
    scene.add(make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right)); */

    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    scene.add(make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random_vec() * Color::random_vec();
                    sphere_material = make_shared<Lambertian>(albedo);
                    scene.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random_vec(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    scene.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    scene.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    scene.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    scene.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    scene.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));


    // Rendering

    camera.render(scene);

}