#include <iostream>

int main() {
    // image specs
    int image_width = 4096;
    int image_height = 2048;

    // P3 for ppm, width and height, max_val for RGB channels
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int i = 0; i < image_height; ++i) 
    {
        std::clog << "\rLines pending for render: " << (image_height - i) << ' ' << std::flush;
        for (int j = 0; j < image_width; ++j) 
        {
            // internal representation
            auto r = double(j) / (image_width - 1);
            auto g = double(i) / (image_height - 1);
            auto b = 0.0;
            
            // scale to [0, 255]
            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);
            
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    std::clog << "\rDone.                      \n";
}
