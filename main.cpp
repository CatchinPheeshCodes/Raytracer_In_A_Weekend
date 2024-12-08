//This is the main file for my raytracer in a weekend project.

//Include header files.
#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

int main () {

    // World.
    hittable_list world;

    //adding metal spheres to our scene.
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    //adding glass sphere on the left.
    auto material_left   = make_shared<dielectric>(1.50);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

    //initialize a camera.
    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.img_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world);
}