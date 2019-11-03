/* camera.h
 * Defines the camera class, which represents a simple axis-aligned camera
 * based on the ray-tracing tutorial at https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf
 * 
 * Melody Mao
 * Fall 2019
 */

#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera
{
    public:
        camera() {
            lower_left_corner = vec3(-2.0, -1.0, -1.0);
            horizontal = vec3(4.0, 0.0, 0.0); //TODO: why is this one 4?
            vertical = vec3(0.0, 2.0, 0.0);
            origin = vec3(0.0, 0.0, 0.0);
        }

        //TODO: ?modified from tutorial, took out "- origin" at end to match previous chapter
        //u, v are in image coordinates
        ray get_ray(float u, float v) { return ray(origin, lower_left_corner + vec3::scale(horizontal, u) + vec3::scale(vertical, v) - origin); }

        vec3 origin;
        vec3 lower_left_corner; //of image
        vec3 horizontal;
        vec3 vertical;
};

#endif