#include "common.h"
#include "camera.h"
#include "Primitives/sphere.h"
#include "Materials/material.h"
#include "Scenes/polygon_scenes.h"
#include "Scenes/sphere_scenes.h"


int main(){
    Camera camera = Camera();
    HittableList scene = HittableList();
    coloured_triangles(scene, camera);
    camera.render(scene);

}