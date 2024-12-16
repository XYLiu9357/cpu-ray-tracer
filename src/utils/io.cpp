/**io.cpp
*
* Utilities for IO-related tasks.
*
*/

#include "utils/interval.hpp"
#include "utils/io.hpp"

void write_ppm(std::ostream& out, const std::vector<std::vector<Color>> &arr)
{
    for (const auto &row : arr)
    {
        for (const auto & pixel_color : row)
        {
            auto r = pixel_color.x();
            auto g = pixel_color.y();
            auto b = pixel_color.z();
            
            // Gamma correction
            r = linear_to_gamma(r, 2);
            g = linear_to_gamma(g, 2);
            b = linear_to_gamma(b, 2);

            // [0,1] -> [0,255].
            static const Interval intensity(0.000, 0.999);
            int rbyte = int(256 * intensity.clamp(r));
            int gbyte = int(256 * intensity.clamp(g));
            int bbyte = int(256 * intensity.clamp(b));

            out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
        }
    }
}

