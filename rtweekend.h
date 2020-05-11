#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <memory>
#include <cmath>
#include <cstdlib>
#include <limits>

// Using
using std::shared_ptr;
using std::make_shared;

// Constants
const double pi = 3.14159265358979323846;
const double infinity = std::numeric_limits<double>::infinity();    // Representation of positive infinity, if available.

// Utilities
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }  // choose min between a and b
inline double ffmax(double a, double b) { return a >= b ? a : b; }  // choose max between a and b

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);                               // +1 because we want 0 <= rand < 1
}

inline double random_double(double min, double max) {
    return min + random_double() * (max - min);
}

inline double clamp(double x, double min, double max) {
    if (x > max) return max;
    if (x < min) return min;
    return x;
}

// Common headers
#include "ray.h"
#include "vec3.h"

#endif /* RTWEEKEND_H */
