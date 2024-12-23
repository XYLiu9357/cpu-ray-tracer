/**color.hpp
*
* Color is an alias for Vec3. 
* The file contains some helper functions for color.
*
*/

#include <cmath>
#include "elements/color.hpp"
#include "utils/interval.hpp"

void write_color(std::ostream& out, const Color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

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

