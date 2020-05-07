#include "ray.h"

#include <iostream>

bool hitSphere(const vec3 &center, double radius, const ray &r) {
    // construct quadratic formula, return discriminant > 0
    // discriminant is larger than zero if ray intersects with sphere at two points
    vec3 centerVec = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2 * dot(r.direction(), centerVec);
    auto c = dot(centerVec, centerVec) - radius * radius;
    double discriminant = b*b - 4*a*c;
    return discriminant > 0;
}

vec3 rayColour(const ray &r) {
    if (hitSphere(vec3(0,0,-1), 0.5, r))
        return vec3(1.0, 0.0, 0.0);
    vec3 unitDir = unitVector(r.direction());
    auto t = 0.5*(unitDir.y() + 1.0); // this scales the unit vector's y value from [-1, 1] to a scale of [0, 1]
    // blendedVal = (1-t)*initVal + t*andVal
    // we return: (1-t)*white + t*blue
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main() {
    const int image_width = 200;
    const int image_height = 100;

    std::cout << "P3\n" << image_width << ' '  << image_height << "\n255\n";

    // define coordinate constants
    vec3 lowerLeftCorner(-2.0, -1.0, -1.0);
    vec3 orig(0.0, 0.0, 0.0);

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            // first print:
            // auto r = double(i) / image_width;
            // auto g = double(j) / image_height;
            // auto b = 0.2;
            // int ir = static_cast<int>(255.999 * r);
            // int ig = static_cast<int>(255.999 * g);
            // int ib = static_cast<int>(255.999 * b);
            // std::cout << ir << ' ' << ig << ' ' << ib << '\n';

            // first print using vec3.h:
            // vec3 colour(double(i) / image_width, double(j) / image_height, 0.2);
            // colour.writeColour(std::cout);

            // for each pixel, create a ray from origin to that pixel
            // get coordinate of pixel
            auto u = double(i) / image_width;
            auto v = double(j) / image_height;
            vec3 pixelCoord = lowerLeftCorner + vec3(u * 4.0, 0.0, 0.0) + vec3(0.0, v * 2.0, 0.0);
            // get colour of ray and write
            ray pixelRay = ray(orig, pixelCoord);
            rayColour(pixelRay).writeColour(std::cout);
        }
    }
    std::cerr << "\nDone.\n";
}
