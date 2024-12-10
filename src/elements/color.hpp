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

void write_color(std::ostream& out, const Color& pixel_color);

#endif
