#include "rtweekend.h"

#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#include <iostream>

vec3 rayColour(const ray& r, const hittable& world, int depth) {
    // exceeded ray bounce limit, no more light gathered
    if (depth <= 0) return vec3(0,0,0);

    hitRecord rec;
    if (world.hit(r, 0.001, infinity, rec)) {
        // return 0.5*(rec.normal + vec3(1.0, 1.0, 1.0));      // norm visualizer
        // vec3 target = rec.normal + randomInUnitSphere();                    // cos^3(phi) diffuse renderer
        // vec3 target = rec.normal + randomUnitVector();                      // Lambertian (cos(phi)) diffuse renderer
        // vec3 target = randomInHemisphere(rec.normal);                       // Hemispherical scattering

        vec3 attenuation;
        ray scatterDir;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scatterDir))
            return attenuation * rayColour(scatterDir, world, depth-1);
        return vec3(0,0,0);     // new ray points randomly outward from surface of contact
    }

    // render blue white gradient bg
    vec3 unitDir = unitVector(r.direction());
    auto t = 0.5*(unitDir.y() + 1.0); // this scales the unit vector's y value from [-1, 1] to a scale of [0, 1]
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main() {
    const int imageWidth = 200;
    const int imageHeight = 100;
    const int samplesPerPixel = 100;
    const int maxDepth = 50;

    std::cout << "P3\n" << imageWidth << ' '  << imageHeight << "\n255\n";

    hittableList world;
    world.add(make_shared<sphere>(
        vec3(0,0,-1), 0.5, make_shared<lambertian>(vec3(0.1, 0.2, 0.5))));                  // middle sphere
    world.add(make_shared<sphere>(
        vec3(0,-100.5,-1), 100, make_shared<lambertian>(vec3(0.8, 0.8, 0.0))));             // the ground

    world.add(make_shared<sphere>(vec3(1,0,-1), 0.5, make_shared<metal>(vec3(0.8, 0.6, 0.2), 0.3)));        // right sphere
    // world.add(make_shared<sphere>(vec3(-1,0,-1), 0.5, make_shared<metal>(vec3(0.8, 0.8, 0.8), 0.3)));       // left sphere
    world.add(make_shared<sphere>(vec3(-1,0,-1), 0.5, make_shared<dielectric>(1.5)));
    world.add(make_shared<sphere>(vec3(-1,0,-1), -0.45, make_shared<dielectric>(1.5)));     // create a hollow glass sphere

    camera cam;

    for (int j = imageHeight-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            // for each pixel, take a certain number of randomly-selected rays and add them together
            vec3 colour(0,0,0);
            for (int s = 0; s < samplesPerPixel; ++s) {
                auto u = random_double(i, i + 1.0) / imageWidth;
                auto v = random_double(j, j + 1.0) / imageHeight;
                ray sampleRay = cam.getRay(u, v);
                colour += rayColour(sampleRay, world, maxDepth);
            }
            colour.writeColour(std::cout, samplesPerPixel);
        }
    }
    std::cerr << "\nDone.\n";
}
