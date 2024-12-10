/**interval.hpp
*
* Interval utilities.
*
*/

#ifndef INTERVAL_H
#define INTERVAL_H

class Interval {
public:
    double min, max;
    Interval();
    Interval(double min, double max);

    double size() const;
    bool contains(double x) const; // Include boundaries
    bool surrounds(double x) const; // Exclude boundaries
    static const Interval empty, universe;
};

#endif

