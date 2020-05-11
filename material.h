#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "hittable.h"

class material {
    public:
        virtual bool scatter(
            const ray& ray_in, const hitRecord& rec, vec3& attenuation, ray& ray_out
        ) const = 0;
};

class lambertian: public material {
    public:
        lambertian(const vec3& a) : albedo(a) {}

        virtual bool scatter(
            const ray& ray_in, const hitRecord& rec, vec3& attenuation, ray& ray_out
        ) const {
            vec3 scatterDir = rec.normal + randomUnitVector();
            ray_out = ray(const_cast<vec3&>(rec.point), scatterDir);
            attenuation = albedo;
            return true;
        };
    
    public:
        vec3 albedo;
};

class metal: public material {
    public:
        metal(const vec3& a, double f) : albedo(a), fuzz(clamp(f, 0, 1)) {}

        virtual bool scatter(
            const ray& ray_in, const hitRecord& rec, vec3& attenuation, ray& ray_out
        ) const {
            vec3 reflectDir = reflect(unitVector(ray_in.direction()), rec.normal);
            reflectDir += fuzz*randomInUnitSphere();
            ray_out = ray(const_cast<vec3&>(rec.point), reflectDir);
            attenuation = albedo;
            return true;
        };


    public:
        vec3 albedo;
        double fuzz;    // a value between 0 and 1
};

#endif /* MATERIAL_H */
