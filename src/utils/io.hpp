/**io.hpp
*
* Utilities for IO-related tasks.
*
*/

#include <iostream>
#include <vector>
#include <string>

#include "elements/color.hpp"

void write_ppm(std::ostream& out, const std::vector<std::vector<Color>> &arr);

