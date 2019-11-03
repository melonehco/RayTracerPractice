/* hitable.h
 * Defines the abstract hitable class
 * based on the ray-tracing tutorial at https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf
 * 
 * Melody Mao
 * Fall 2019
 */

#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

struct hit_record {
    float t; //t along ray
    vec3 p; //point on surface
    vec3 normal; //surface normal
};

class hitable
{
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
        //TODO: what does this = 0 mean
};

#endif