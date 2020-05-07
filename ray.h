#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    public:
        ray() {}
        ray(vec3 &origin, vec3 &direction) : orig(origin), dir(direction) {};

        vec3 origin() const { return orig; }        // TODO: why are these here if orig and dir are under public?
        vec3 direction() const { return dir; }

        // taking a point along the ray
        vec3 at(double t) const {       // TODO: why is this const?
            // p(t) = a + tb
            return orig + t * dir;
        }

    public:
        vec3 orig;
        vec3 dir;
};

#endif /* RAY_H */
