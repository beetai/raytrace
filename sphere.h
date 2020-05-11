#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "ray.h"

class sphere: public hittable {
    public:
        sphere() {};
        sphere(vec3 cen, double r, shared_ptr<material> m)
            : center(cen), radius(r), mat_ptr(m) {};

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;

    public:
        vec3 center;
        double radius;
        shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 center_vec = r.origin() - center;
    auto a = r.direction().sum_of_square();
    auto half_b = dot(r.direction(), center_vec);
    auto c = center_vec.sum_of_square() - radius * radius;
    auto discriminant = half_b*half_b - a*c;
    if (discriminant > 0) {
        // take first t value where hit occurs
        auto t = (-half_b - sqrt(discriminant)) / a;
        if (t < t_max && t > t_min) {
            rec.t = t;
            rec.point = r.at(t);
            vec3 outward_normal = (rec.point - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
        // take second t value where hit occurs
        t = (-half_b + sqrt(discriminant)) / a;
        if (t < t_max && t > t_min) {
            rec.t = t;
            rec.point = r.at(t);
            vec3 outward_normal = (rec.point - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
};

#endif /* SPHERE_H */
