#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class camera {
    public:
        camera() {
            origin = vec3(0,0,0);
            lower_left_corner = vec3(-2,-1,-1);
            frame_width = 4.0;
            frame_height = 2.0;
        }

        ray get_ray(double u, double v) {
            vec3 point_coord = lower_left_corner + vec3(u * frame_width, 0.0, 0.0) + vec3(0.0, v * frame_height, 0.0) - origin;
            return ray(origin, point_coord);
        }

    public:
        vec3 origin;
        vec3 lower_left_corner;
        // vec3 frame_width;
        double frame_width;
        // vec3 frame_height;
        double frame_height;
};

#endif /* CAMERA_H */
