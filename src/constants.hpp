/**constants.hpp
*
* Constants.
*
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <limits>

#define PI 3.1415926535897932385
const double INF = std::numeric_limits<double>::infinity();
inline double degrees_to_radians(double degrees) { return degrees * PI / 180.0; }

#endif // CONSTANTS_h
