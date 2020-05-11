#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

struct vec3 {
    public:
        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() { return e[0]; }
        double y() { return e[1]; }
        double z() { return e[2]; }

        vec3 operator-() { return vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }             // TODO: understand this
        double& operator[](int i) { return e[i]; }                  // TODO: understand this

        // vector addition
        vec3& operator+=(const vec3 &v) {
            // TODO: why is it not: 
            // return vec3(e[0] + v.e[0], ..., ...)
            // because initiation is expensive?
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        // scalar multiplication
        vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;          
        }

        // scalar division
        vec3& operator/=(const double t) {
            e[0] /= t;
            e[1] /= t;
            e[2] /= t;
            return *this; // what is a better way to do this? use already defined function
        }

        double sum_of_square() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        double length() {
            return sqrt(sum_of_square());
        }

        void write_colour(std::ostream &out, int samples_per_pixel) {
            // Divide color total by number of samples per pixel
            auto scale = 1.0 / samples_per_pixel;     // this is because multiplying is better than dividing? check
            auto r = sqrt(e[0] * scale);            // sqrt for gamma correction: gamma 2 (take value^(1/gamma))
            auto g = sqrt(e[1] * scale);
            auto b = sqrt(e[2] * scale);
            
            // Write the translated [0,255] value of each component
            out << static_cast<int>(255.999 * clamp(r, 0, 0.9999)) << ' '
                << static_cast<int>(255.999 * clamp(g, 0, 0.9999)) << ' '
                << static_cast<int>(255.999 * clamp(b, 0, 0.9999)) << '\n';
        }

        inline static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        inline static vec3 random(double min, double max) {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }

    public:
        double e[3];

};

// vec3 util functions 

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' '
                << v.e[1] << ' '
                << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator-(const vec3 &u) {
    return vec3(-u.e[0], -u.e[1], -u.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3 &v, double t) {
    return v * (1/t);
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
            + u.e[1] * v.e[1]
            + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] -  u.e[2] * v.e[1],
                u.e[2] * v.e[0] -  u.e[0] * v.e[2],
                u.e[0] * v.e[1] -  u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

vec3 random_in_unit_sphere() {
    while (true) {
        vec3 p = vec3::random(-1,1);
        if (p.sum_of_square() >= 1) continue;
        return p;
    }
}

vec3 random_unit_vector() {
    auto theta = random_double(0, 2*pi);
    auto z = random_double(-1, 1);
    auto r = random_double(0, 1);
    return vec3(r*cos(theta), r*sin(theta), z);
}

vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0)    // point in same direction
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

vec3 reflect(const vec3& in, const vec3& norm) {
    return in - 2*dot(in, norm)*norm;
}

vec3 refract(const vec3& in, const vec3& norm, double eta_over_etap) {
    auto cos_theta = dot(-in, norm);
    vec3 r_out_parallel = eta_over_etap * (in + cos_theta * norm);
    vec3 r_out_perp = - sqrt(1.0 - r_out_parallel.sum_of_square()) * norm;
    return r_out_parallel + r_out_perp;
}

#endif /* VEC3_H */
