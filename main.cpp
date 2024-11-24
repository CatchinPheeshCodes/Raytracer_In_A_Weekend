//This is the main file for my raytracer in a weekend project.
#include <iostream>
int main () {
    //image boundaries.
    int img_width = 256;
    int img_height = 256;

    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    //for loop to iterate over all pixels in the image.
    for (int j = 0; j < img_height; ++j) {
        for(int i = 0; i < img_width; ++i) {
            auto r = double(i) / (img_width - 1);
            auto g = double(j) / (img_height - 1);
            auto b = 0.0;

            int ir = int(255.000 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    } 
}