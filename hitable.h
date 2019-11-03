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

class material; //lets compiler know pointer in hit_record is to a class

struct hit_record {
    float t; //t along ray
    vec3 p; //point on surface
    vec3 normal; //surface normal
    material *mat_ptr;
};

class hitable
{
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
        //"= 0" makes hit a pure virtual function, which means that it must be overridden by a subclass
};

#endif