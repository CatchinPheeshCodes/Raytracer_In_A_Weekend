#ifndef COLOR_H
#define COLOR_H

#include "rtweekend.h"

using color = vec3;

//writes a pixel's color to std output stream.
void write_color(std::ostream& out, const color& pixel_color) {

    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    //Write the pixel's color components out.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif