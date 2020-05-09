#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hitRecord {
    vec3 point;
    vec3 normal;
    double t;
    bool frontFace;

    inline void setFaceNormal(const ray& r, const vec3& outwardNormal) {
        // if ray and outward norm are in same dir, ray is inside, else it is outside
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class hittable {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hitRecord& rec) const = 0;
};

#endif /* HITTABLE_H */
