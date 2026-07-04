#ifndef INTERVAL
#define INTERVAL

#include "common.h"

class Interval {
    public: 

        double max;
        double min;

        Interval() : max(infinity), min(-infinity) {}
        Interval(double min, double max) : max(max), min(min) {}


        double size() {return max - min;}
        double contains(double x) const{
            return min <= x && x <= max;
        }

        double surrounds(double x) const{
            return min < x && x < max;
        }

        double clamp(double x) const {
            if (x < min) { return min;}
            if (x > max) {return max;}
            return x;
        }

        static const Interval empty, universe;
};

const Interval Interval::empty    = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

#endif