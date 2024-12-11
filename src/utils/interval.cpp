/**interval.cpp
*
* Interval utilities.
*
*/

#include "constants.hpp"
#include "utils/interval.hpp"

const Interval Interval::empty = Interval(+INF, -INF);
const Interval Interval::universe = Interval(-INF, +INF);

Interval::Interval() : min(+INF), max(-INF) {} // Default interval is empty
Interval::Interval(double min, double max) : min(min), max(max) {}

double Interval::size() const { return max - min; }
bool Interval::contains(double x) const { return min <= x && x <= max; }
bool Interval::surrounds(double x) const { return min < x && x < max; }

double Interval::clamp(double x) const
{
    if (x < min) return min;
    else if (x > max) return max;
    else return x;
}

