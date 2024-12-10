/**main.cpp
*
* Main
*
*/

#include <iostream>

#include "elements/color.hpp"

int main() {
    // image specs
    int image_width = 256;
    int image_height = 256;

    // P3 for ppm, width and height, max_val for RGB channels
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int i = 0; i < image_height; ++i) 
    {
        std::clog << "\rLines pending for render: " << (image_height - i) << ' ' << std::flush;
        for (int j = 0; j < image_width; ++j) 
        {
            auto pixel_color = color(double(i)/(image_width-1), double(j)/(image_height-1), 0);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                      \n";
}
