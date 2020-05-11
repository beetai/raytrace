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

// Polynomial approximation by Christopher Schlick
double schlick(double cosine,double ref_idx) {
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 *= r0;
    return r0 + (1-r0)*pow((1 - cosine), 5);
}

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

class dielectric: public material {
    public:
        dielectric(double ri) : ref_idx(ri) {}

        virtual bool scatter(
            const ray& ray_in, const hitRecord& rec, vec3& attenuation, ray& ray_out
        ) const {
            attenuation = vec3(1,1,1);      // glass/dielectric surface absorbs nothing
            // determine if air->sphere refraction or sphere->air refraction
            double eta_over_etap;
            if (rec.frontFace) {
                eta_over_etap = 1 / ref_idx;
            } else {
                eta_over_etap = ref_idx;
            }

            // determine if reflect or refract
            vec3 unit_dir_in = unitVector(ray_in.direction());

            double cos_theta = ffmin(dot(-unit_dir_in, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta*cos_theta);
            if (eta_over_etap * sin_theta > 1.0) {
                // no solution to Snell's law: must reflect
                vec3 reflectDir = reflect(unit_dir_in, rec.normal);
                ray_out = ray(const_cast<vec3&>(rec.point), reflectDir);
                return true;
            }

            // can refract
            double reflect_prob = schlick(cos_theta, eta_over_etap);
            if (random_double() < reflect_prob) {
                vec3 reflectDir = reflect(unit_dir_in, rec.normal);
                ray_out = ray(const_cast<vec3&>(rec.point), reflectDir);
                return true;
            }
            vec3 refract_dir = refract(unit_dir_in, rec.normal, eta_over_etap);
            ray_out = ray(const_cast<vec3&>(rec.point), refract_dir);
            return true;
        }

    public:
        double ref_idx;
};

#endif /* MATERIAL_H */
