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
        metal(const vec3& a) : albedo(a) {}

        virtual bool scatter(
            const ray& ray_in, const hitRecord& rec, vec3& attenuation, ray& ray_out
        ) const {
            vec3 reflectDir = reflect(unitVector(ray_in.direction()), rec.normal);
            ray_out = ray(const_cast<vec3&>(rec.point), reflectDir);
            attenuation = albedo;
            return true;
        };


    public:
        vec3 albedo;
};

#endif /* MATERIAL_H */
