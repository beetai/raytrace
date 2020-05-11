#include "rtweekend.h"

#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#include <iostream>

vec3 ray_colour(const ray& r, const hittable& world, int depth) {
    // exceeded ray bounce limit, no more light gathered
    if (depth <= 0) return vec3(0,0,0);

    hit_record rec;
    if (world.hit(r, 0.001, infinity, rec)) {
        // return 0.5*(rec.normal + vec3(1.0, 1.0, 1.0));      // norm visualizer
        // vec3 target = rec.normal + random_in_unit_sphere();                    // cos^3(phi) diffuse renderer
        // vec3 target = rec.normal + random_unit_vector();                      // Lambertian (cos(phi)) diffuse renderer
        // vec3 target = random_in_hemisphere(rec.normal);                       // Hemispherical scattering

        vec3 attenuation;
        ray scatter_dir;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scatter_dir))
            return attenuation * ray_colour(scatter_dir, world, depth-1);
        return vec3(0,0,0);     // new ray points randomly outward from surface of contact
    }

    // render blue white gradient bg
    vec3 unit_dir = unit_vector(r.direction());
    auto t = 0.5*(unit_dir.y() + 1.0); // this scales the unit vector's y value from [-1, 1] to a scale of [0, 1]
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main() {
    const int image_width = 200;
    const int image_height = 100;
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    const auto aspect_ratio = double(image_width) / image_height;

    std::cout << "P3\n" << image_width << ' '  << image_height << "\n255\n";

    hittable_list world;
    world.add(make_shared<sphere>(
        vec3(0,0,-1), 0.5, make_shared<lambertian>(vec3(0.1, 0.2, 0.5))));                  // middle sphere
    world.add(make_shared<sphere>(
        vec3(0,-100.5,-1), 100, make_shared<lambertian>(vec3(0.8, 0.8, 0.0))));             // the ground

    world.add(make_shared<sphere>(vec3(1,0,-1), 0.5, make_shared<metal>(vec3(0.8, 0.6, 0.2), 0.0)));        // right sphere
    // world.add(make_shared<sphere>(vec3(-1,0,-1), 0.5, make_shared<metal>(vec3(0.8, 0.8, 0.8), 0.3)));       // left sphere
    world.add(make_shared<sphere>(vec3(-1,0,-1), 0.5, make_shared<dielectric>(1.5)));
    world.add(make_shared<sphere>(vec3(-1,0,-1), -0.45, make_shared<dielectric>(1.5)));     // create a hollow glass sphere

    vec3 vup(0,1,0);
    camera cam(vec3(-2,2,1), vec3(0,0,-1), vup, 70, aspect_ratio);

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            // for each pixel, take a certain number of randomly-selected rays and add them together
            vec3 colour(0,0,0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = random_double(i, i + 1.0) / image_width;
                auto v = random_double(j, j + 1.0) / image_height;
                ray sample_ray = cam.get_ray(u, v);
                colour += ray_colour(sample_ray, world, max_depth);
            }
            colour.write_colour(std::cout, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
}
