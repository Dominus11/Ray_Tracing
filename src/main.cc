#include "common.h"
#include "camera.h"
#include "Primitives/sphere.h"
#include "Materials/material.h"
#include "Scenes/quad_scenes.h"
#include "Scenes/sphere_scenes.h"


int main(){
    Camera camera = Camera();
    HittableList scene = HittableList();
    four_planes(scene, camera);
    camera.render(scene);

}