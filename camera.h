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

//returns a random point in the unit disk
vec3 random_in_unit_disk()
{
    vec3 p;
    do
    {
        p = vec3::scale(vec3(drand48(), drand48(), 0), 2.0) -  vec3(1, 1, 0);
    } while (vec3::dot(p, p) >= 1.0);
    return p;
}

class camera
{
    public:
        //takes in vfov in degrees
        camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist) {
            lens_radius = aperture/2.0;

            float theta = vfov * M_PI / 180.0; //convert to radians
            float half_height = tan(theta/2); //based on geometry, w/ plane at z = -1
            float half_width = aspect * half_height;
            
            origin = lookfrom;
            w = vec3::unit_vector(lookfrom - lookat); //I think this one is VPN
            u = vec3::unit_vector( vec3::cross(vup, w) ); //I think this is equivalent to our u before
            v = vec3::cross(w, u);

            lower_left_corner = origin - vec3::scale(u, half_width*focus_dist) - vec3::scale(v, half_height*focus_dist) - vec3::scale(w, focus_dist);
            horizontal = vec3::scale(u, 2*half_width*focus_dist);
            vertical = vec3::scale(v, 2*half_height*focus_dist);
        }

        ray get_ray(float s, float t)
        {
            vec3 rd = vec3::scale(random_in_unit_disk(), lens_radius);
            vec3 offset = vec3::scale(u, rd.x()) + vec3::scale(v, rd.y());
            return ray(origin + offset,
                       lower_left_corner + vec3::scale(horizontal, s) + vec3::scale(vertical, t) - origin - offset);
        }

        vec3 origin;
        vec3 lower_left_corner; //of image(?)
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        float lens_radius;
};

#endif