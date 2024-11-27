//This is the main file for my raytracer in a weekend project.

//Include header files.
#include "vec3.h"
#include "color.h"

#include <iostream>

int main () {
    //image boundaries.
    int img_width = 256;
    int img_height = 256;

    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    //nested for loops to iterate over all pixels in the image.
    for (int j = 0; j < img_height; ++j) {
        //Counter for remaining lines to be processed. j = current line. remaining = total lines - j.
        std::clog << "\rScanlines remaining: " << (img_height - j) << ' ' << std::flush;
        for(int i = 0; i < img_width; ++i) {
            //Define pixel color.
            auto pixel_color = color(double(i)/(img_width - 1), double(j)/(img_height - 1), 0);
            //Write out pixel color.
            write_color(std::cout, pixel_color);
        }
    } 
    std::clog << "\rDone.                  \n";
}