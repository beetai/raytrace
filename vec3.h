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

        double sumOfSquare() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        double length() {
            return sqrt(sumOfSquare());
        }

        void writeColour(std::ostream &out) { // TODO: make sense of the parameter
            // Write the translated [0,255] value of each component
            out << static_cast<int>(255.999 * e[0]) << ' '
                << static_cast<int>(255.999 * e[1]) << ' '
                << static_cast<int>(255.999 * e[2]) << '\n';
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

inline vec3 unitVector(vec3 v) {
    return v / v.length();
}

#endif /* VEC3_H */
