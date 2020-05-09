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
inline double degreesToRadians(double degrees) {
    return degrees * pi / 180;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }  // choose min between a and b
inline double ffmax(double a, double b) { return a >= b ? a : b; }  // choose max between a and b

// Common headers
#include "ray.h"
#include "vec3.h"

#endif /* RTWEEKEND_H */
