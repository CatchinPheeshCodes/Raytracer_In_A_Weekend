#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
    public:
        //image boundaries.
        double aspect_ratio = 1.0;
        int img_width = 100;

        void render(const hittable& world) {
            initialize();

            std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

            //nested for loops to iterate over all pixels in the image.
             for (int j = 0; j < img_height; ++j) {
                //Counter for remaining lines to be processed. j = current line. remaining = total lines - j.
                std::clog << "\rScanlines remaining: " << (img_height - j) << ' ' << std::flush;
                for(int i = 0; i < img_width; ++i) {
                    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                    auto ray_direction = pixel_center - camera_center;
                    ray r(camera_center, ray_direction);

                    color pixel_color = ray_color(r, world);
                    write_color(std::cout, pixel_color);
                }
            }
            std::clog << "\rDone.                  \n";
        }
    private:
        int img_height;
        point3 camera_center;
        point3 pixel00_loc;
        vec3 pixel_delta_u;
        vec3 pixel_delta_v;

        void initialize() {
            img_height = int(img_width / aspect_ratio);
            img_height = (img_height < 1) ? 1 : img_height;

            camera_center = point3(0, 0, 0);

            //viewport dimensions.
            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(img_width) / img_height);

            //calculate vectors across the horizontal and down the vertical viewport edges.
            auto viewport_u = vec3(viewport_width, 0, 0);
            auto viewport_v = vec3(0, -viewport_height, 0);

            //calculate the horizontal and vertical delta vectors from pixel to pixel.
            pixel_delta_u = viewport_u / img_width;
            pixel_delta_v = viewport_v / img_height;

            //calculate the location of the upper left pixel p(0, 0).
            auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        }
        color ray_color(const ray& r, const hittable& world) const {
            hit_record rec;
            if(world.hit(r, interval(0, infinity), rec)) {
                return 0.5 * (rec.normal + color(1, 1, 1));
            }
    
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
        }
};

#endif