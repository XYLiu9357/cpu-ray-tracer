/**color.hpp
*
* Color and related functions..
*
*/

#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "utils/vec3.hpp"

// Color is just an alias for Vec3
using Color = Vec3;

inline double linear_to_gamma(double linear_component, double gamma)
{
    if (gamma <= 0) throw std::invalid_argument("Color: gamma factor should be a positive real number."); 
    else if (linear_component > 0) return pow(linear_component, 1 / gamma);
    else return 0;
}

void write_color(std::ostream& out, const Color& pixel_color);

#endif
