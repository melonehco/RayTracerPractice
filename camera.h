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
        //takes in vfov in degrees
        camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect) {
            vec3 u, v, w;
            float theta = vfov * M_PI / 180.0; //convert to radians
            float half_height = tan(theta/2); //based on geometry, w/ plane at z = -1
            float half_width = aspect * half_height;
            
            origin = lookfrom;
            w = vec3::unit_vector(lookfrom - lookat); //I think this one is VPN
            u = vec3::unit_vector( vec3::cross(vup, w) ); //I think this is equivalent to our u before
            v = vec3::cross(w, u);

            lower_left_corner = origin - vec3::scale(u, half_width) - vec3::scale(v, half_height) - w;
            horizontal = vec3::scale(u, 2*half_width);
            vertical = vec3::scale(v, 2*half_height);
        }

        //TODO: ?modified from tutorial, took out "- origin" at end to match previous chapter
        //u, v are in image coordinates
        ray get_ray(float u, float v) { return ray(origin, lower_left_corner + vec3::scale(horizontal, u) + vec3::scale(vertical, v) - origin); }

        vec3 origin;
        vec3 lower_left_corner; //of image(?)
        vec3 horizontal;
        vec3 vertical;
};

#endif