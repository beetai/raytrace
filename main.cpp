#include "rtweekend.h"

#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>

vec3 rayColour(const ray& r, const hittable& world, int depth) {
    // exceeded ray bounce limit, no more light gathered
    if (depth <= 0) return vec3(0,0,0);

    hitRecord rec;
    if (world.hit(r, 0.001, infinity, rec)) {
        // return 0.5*(rec.normal + vec3(1.0, 1.0, 1.0));      // norm visualizer
        vec3 target = rec.normal + randomUnitVector();
        return 0.5 * rayColour(ray(rec.point, target), world, depth-1);  // new ray points randomly outward from surface of contact
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
    world.add(make_shared<sphere>(vec3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(vec3(0,-100.5,-1), 100));

    camera cam;

    for (int j = imageHeight-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            // // for each pixel, create a ray from origin to that pixel
            // // get coordinate of pixel
            // auto u = double(i) / imageWidth;
            // auto v = double(j) / imageHeight;
            // // get colour of ray and write
            // ray pixelRay = cam.getRay(u, v);
            // rayColour(pixelRay, world).writeColour(std::cout, 1);

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
