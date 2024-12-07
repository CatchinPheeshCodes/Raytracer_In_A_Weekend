#ifndef INTERVAL_H
#define INTERVAL_H

#include "rtweekend.h"
//interval class manages real valued intervals.
class interval {
    public:
        double min, max;
        //default is empty.
        interval() : min(+infinity), max(-infinity) {}
        //constructor.
        interval(double min, double max) : min(min), max(max) {}

        //interval size. distance between min and max.
        double size() const {
            return max - min;
        }
        //interval contains x?
        bool contains(double x) const {
            return min <= x && x <= max;
        }
        //x surrounds interval?
        bool surrounds(double x) const {
            return min < x && x < max;
        }
        //ensures that a return value is within bounds. 
        double clamp(double x) const {
            if (x < min) return min;
            if (x > max) return max;
            return x;
        }

        static const interval empty, universe;
};

const interval interval::empty    = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

#endif