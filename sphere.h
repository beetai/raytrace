#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "ray.h"

class sphere: public hittable {
    public:
        sphere() {};
        sphere(vec3 cen, double r) : center(cen), radius(r) {};

        virtual bool hit(const ray& r, double t_min, double t_max, hitRecord& rec) const;

    public:
        vec3 center;
        double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hitRecord& rec) const {
    vec3 centerVec = r.origin() - center;
    auto a = r.direction().sumOfSquare();
    auto halfB = dot(r.direction(), centerVec);
    auto c = centerVec.sumOfSquare() - radius * radius;
    auto discriminant = halfB*halfB - a*c;
    if (discriminant > 0) {
        // take first t value where hit occurs
        auto t = (-halfB - sqrt(discriminant)) / a;
        if (t < t_max && t > t_min) {
            rec.t = t;
            rec.point = r.at(t);
            vec3 outwardNormal = (rec.point - center) / radius;
            rec.setFaceNormal(r, outwardNormal);
            return true;
        }
        // take second t value where hit occurs
        auto t = (-halfB + sqrt(discriminant)) / a;
        if (t < t_max && t > t_min) {
            rec.t = t;
            rec.point = r.at(t);
            vec3 outwardNormal = (rec.point - center) / radius;
            rec.setFaceNormal(r, outwardNormal);
            return true;
        }
    }
    return false;
};

#endif /* SPHERE_H */
