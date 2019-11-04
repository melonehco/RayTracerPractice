/* material.h
 * Defines the abstract material class
 * based on the ray-tracing tutorial at https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf
 * 
 * Melody Mao
 * Fall 2019
 */

#ifndef MATERIALH
#define MATERIALH

#include "ray.h"

//returns a random point in the unit sphere
vec3 random_in_unit_sphere()
{
    vec3 p;
    do //keep randomizing in unit cube until we get a point that's inside unit sphere
    {
        p = vec3::scale((vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1)),
                        2.0);
    } while (p.squared_length() >= 1.0);

    return p;
}

//reflects v about n
vec3 reflect(const vec3& v, const vec3& n)
{
    return v - vec3::scale(n, 2*vec3::dot(v, n));
}

class material
{
    public:
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

#endif