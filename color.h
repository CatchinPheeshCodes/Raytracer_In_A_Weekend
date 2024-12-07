#ifndef COLOR_H
#define COLOR_H

#include "rtweekend.h"
#include "vec3.h"
#include "interval.h"

using color = vec3;

//writes a pixel's color to std output stream.
void write_color(std::ostream& out, const color& pixel_color) {

    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    //Write the pixel's color components out.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif