#include "rtweekend.h"

#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>

vec3 rayColour(const ray& r, const hittable& world) {
    // basic sphere collision test (hitSphere() only checks if ray hits sphere):
    // if (hitSphere(vec3(0,0,-1), 0.5, r))
    //     return vec3(1.0, 0.0, 0.0);

    // norm visualization:
    // vec3 center = vec3(0,0,-1);
    // auto t = hitSphere(center, 0.5, r);
    // if (t > 0) {
    //     // get point of contact
    //     vec3 pc = r.at(t);
    //     vec3 surfNorm = unitVector(pc - center);
    //     return 0.5*(surfNorm + vec3(1.0, 1.0, 1.0));
    // }

    hitRecord rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5*(rec.normal + vec3(1.0, 1.0, 1.0));
    }

    // render blue white gradient bg
    vec3 unitDir = unitVector(r.direction());
    auto t = 0.5*(unitDir.y() + 1.0); // this scales the unit vector's y value from [-1, 1] to a scale of [0, 1]
    // blendedVal = (1-t)*initVal + t*andVal
    // we return: (1-t)*white + t*blue
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main() {
    const int imageWidth = 200;
    const int imageHeight = 100;
    const int samplesPerPixel = 100;

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
                colour += rayColour(sampleRay, world);
            }
            colour.writeColour(std::cout, samplesPerPixel);
        }
    }
    std::cerr << "\nDone.\n";
}
