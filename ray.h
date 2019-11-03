/* ray.h
 * Defines the ray class
 * based on the ray-tracing tutorial at https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf
 * 
 * Melody Mao
 * Fall 2019
 */

#ifndef RAYH
#define RAYH

#include "vec3.h"

class ray
{
    public:
        ray() {}
        ray(const vec3& a, const vec3& b) { A = a; B = b; }
        vec3 origin() const { return A; }
        vec3 direction() const { return B; }
        vec3 point_at_t(float t) const { return A + vec3::scale(B, t); }

        vec3 A; //ray origin
        vec3 B; //ray direction
};

#endif