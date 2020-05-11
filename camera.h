#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class camera {
    public:
        camera() {
            origin = vec3(0,0,0);
            lowerLeftCorner = vec3(-2,-1,-1);
            frameWidth = 4.0;
            frameHeight = 2.0;
        }

        ray getRay(double u, double v) {
            vec3 pointCoord = lowerLeftCorner + vec3(u * frameWidth, 0.0, 0.0) + vec3(0.0, v * frameHeight, 0.0) - origin;
            return ray(origin, pointCoord);
        }

    public:
        vec3 origin;
        vec3 lowerLeftCorner;
        // vec3 frameWidth;
        double frameWidth;
        // vec3 frameHeight;
        double frameHeight;
};

#endif /* CAMERA_H */
