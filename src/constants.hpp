/**constants.hpp
*
* Constants.
*
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdlib>
#include <limits>

#define PI 3.1415926535897932385
const double INF = std::numeric_limits<double>::infinity();

inline double degrees_to_radians(double degrees) { return degrees * PI / 180.0; }
inline double random_double() { return std::rand() / (RAND_MAX + 1.0); }
inline double random_double(double min, double max) { return min + (max - min) * random_double(); }

#endif // CONSTANTS_h
