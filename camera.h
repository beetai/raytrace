#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class camera {
    public:
        camera(
            vec3 lookfrom, vec3 lookat, vec3 vup,
            double vfov,        // top to bottom in degrees
            double aspect, double aperture, double focus_dist
        ) {
            origin = lookfrom;
            lens_radius = aperture / 2;

            auto theta = degrees_to_radians(vfov);
            auto half_height = tan(theta / 2);
            auto half_width = aspect * half_height;
            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));         // TODO: this part doesn't make sense to me
            v = cross(w, u);

            lower_left_corner = origin
                              - half_width*focus_dist*u
                              - half_height*focus_dist*v
                              - focus_dist*w;

            horizontal = 2*half_width*focus_dist*u;
            vertical = 2*half_height*focus_dist*v;
        }

        ray get_ray(double s, double t) {
            vec3 lens_point = lens_radius * random_in_unit_disk();
            lens_point = u*lens_point.x() + v*lens_point.y();
            lens_point += origin;
            vec3 point_coord = lower_left_corner + s*horizontal + t*vertical - lens_point;
            return ray(lens_point, point_coord);
        }

    public:
        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        double lens_radius;
        vec3 u, v, w;
};

#endif /* CAMERA_H */
