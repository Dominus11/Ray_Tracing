#ifndef QUAD_SCENES_H
#define QUAD_SCENES_H

#include "../common.h"
#include "../camera.h"
#include "../Primitives/hittable_list.h"
#include "../Primitives/quad.h"


void four_planes(HittableList& scene, Camera& cam){
    // Materials
    auto left_red     = make_shared<Lambertian>(Color(1.0, 0.2, 0.2));
    auto back_green   = make_shared<Lambertian>(Color(0.2, 1.0, 0.2));
    auto right_blue   = make_shared<Lambertian>(Color(0.2, 0.2, 1.0));
    auto upper_orange = make_shared<Lambertian>(Color(1.0, 0.5, 0.0));
    auto lower_teal   = make_shared<Lambertian>(Color(0.2, 0.8, 0.8));

    // Quads
    scene.add(make_shared<Quad>(Point3(-3,-2, 5), Vec3(0, 0,-4), Vec3(0, 4, 0), left_red));
    scene.add(make_shared<Quad>(Point3(-2,-2, 0), Vec3(4, 0, 0), Vec3(0, 4, 0), back_green));
    scene.add(make_shared<Quad>(Point3( 3,-2, 1), Vec3(0, 0, 4), Vec3(0, 4, 0), right_blue));
    scene.add(make_shared<Quad>(Point3(-2, 3, 1), Vec3(4, 0, 0), Vec3(0, 0, 4), upper_orange));
    scene.add(make_shared<Quad>(Point3(-2,-3, 5), Vec3(4, 0, 0), Vec3(0, 0,-4), lower_teal));

    cam.aspect_ratio      = 1.0;
    cam.img_width       = 400;
    cam.samps_per_pixel = 100;
    cam.max_depth         = 50;

    cam.vfov     = 80;
    cam.lookfrom = Point3(0,0,9);
    cam.lookat   = Point3(0,0,0);
    cam.vup      = Vec3(0,1,0);

    cam.defocus_angle = 0;
    cam.focus_dist = 10;

    cam.initialise();

}


#endif