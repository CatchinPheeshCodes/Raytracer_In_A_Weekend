#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"

class camera {
    public:
        //image boundaries.
        double aspect_ratio = 1.0;
        int img_width = 100;
        int samples_per_pixel = 10;
        int max_depth = 10;

        double vfov = 90; // vertical view angle (field of view).

        point3 lookfrom = point3(0, 0, 0); // point camera is looking from.
        point3 lookat = point3(0, 0, -1);  // point camera is looking at.
        vec3 vup = vec3(0, 1, 0);          // up direction relative to camera.

        double defocus_angle = 0;
        double focus_dist = 10;

        void render(const hittable& world) {
            initialize();

            std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

            //nested for loops to iterate over all pixels in the image.
             for (int j = 0; j < img_height; ++j) {
                //Counter for remaining lines to be processed. j = current line. remaining = total lines - j.
                std::clog << "\rScanlines remaining: " << (img_height - j) << ' ' << std::flush;
                for(int i = 0; i < img_width; ++i) {
                    color pixel_color(0, 0, 0);
                    for(int sample = 0; sample < samples_per_pixel; ++sample) {
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r, max_depth, world);
                    }
                    write_color(std::cout, pixel_samples_scale * pixel_color);
                }
            }
            std::clog << "\rDone.                  \n";
        }
    private:
        int img_height;             // Rendered image height.
        double pixel_samples_scale; // Color scale factor for a sum of pixels.
        point3 camera_center;       // Camera Center. 
        point3 pixel00_loc;         // Pixel 0, 0 location.
        vec3 pixel_delta_u;         // Right pixel offset.
        vec3 pixel_delta_v;         // Below pixel offset.
        vec3 u, v, w;               // Camera frame basis vectors.
        vec3 defocus_disk_u;
        vec3 defocus_disk_v;

        void initialize() {
            img_height = int(img_width / aspect_ratio);
            img_height = (img_height < 1) ? 1 : img_height;

            pixel_samples_scale = 1.0 / samples_per_pixel;

            camera_center = lookfrom;

            //viewport dimensions.
            auto theta = degrees_to_radians(vfov);
            auto h = std::tan(theta / 2);
            auto viewport_height = 2 * h * focus_dist;
            auto viewport_width = viewport_height * (double(img_width) / img_height);

            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            //calculate vectors across the horizontal and down the vertical viewport edges.
            auto viewport_u = viewport_width * u;   //vector across viewport horizontal edge.
            auto viewport_v = viewport_height * -v; //vector down viewport vertical edge.

            //calculate the horizontal and vertical delta vectors from pixel to pixel.
            pixel_delta_u = viewport_u / img_width;
            pixel_delta_v = viewport_v / img_height;

            //calculate the location of the upper left pixel p(0, 0).
            auto viewport_upper_left = camera_center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

            //calculate teh camera defocus disk basis vectors.
            auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
            defocus_disk_u = u * defocus_radius;
            defocus_disk_v = v * defocus_radius;
        }
        //Constructs camera ray originating from the defocus disk and directed at randomly sampled
        //point around the pixel location.
        ray get_ray(int i, int j) const {

            auto offset = sample_square();
            auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);
            auto ray_origin = (defocus_angle <= 0) ? camera_center : defocus_disk_sample();
            auto ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }
        //Returns the vector to a random point in the [-.5, -.5] - [.5, .5] unit square.
        vec3 sample_square() const {
            return vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }
        point3 defocus_disk_sample() const {
            //Returns a random point in the camera defocus disk.
            auto p = random_in_unit_disk();
            return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
        }
        color ray_color(const ray& r, int depth, const hittable& world) const {
            if(depth <= 0) {
                return color(0, 0, 0);
            }
            hit_record rec;
            if(world.hit(r, interval(0.001, infinity), rec)) {
                ray scattered;
                color attenuation;
                if(rec.mat->scatter(r, rec, attenuation, scattered)) {
                    return attenuation * ray_color(scattered, depth-1, world);
                }
                return color(0, 0, 0);
            }
    
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
        }
};

#endif