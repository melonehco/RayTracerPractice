/* sphere.h
 * Defines the sphere class
 * based on the ray-tracing tutorial at https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf
 * 
 * Melody Mao
 * Fall 2019
 */

#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"
#include "material.h"

class sphere: public hitable //TODO: what is the "public" here for?
{
    public:
        sphere() {}
        sphere(vec3 cen, float r, material *m_ptr) : center(cen), radius(r), mat_ptr(m_ptr) {};
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

        vec3 center;
        float radius;
        material *mat_ptr;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    //math based on manipulating equations defining sphere and ray, as described in ch 4
    vec3 oc = r.origin() - center;
    float a = vec3::dot(r.direction(), r.direction());
    float b = 2.0 * vec3::dot(oc, r.direction());
    float c = vec3::dot(oc, oc) - radius * radius;
    float discriminant = b*b - 4*a*c; //TODO: the tutorial changed this, but it didn't work??
    if (discriminant > 0) //if there is intersection
    {
        float temp = (-b - sqrt(discriminant)) / (2.0*a); //TODO: tutorial changed this as well
        if (temp < t_max && temp > t_min) //if t is within desired interval
        {
            rec.t = temp;
            rec.p = r.point_at_t(temp);
            rec.normal = vec3::scale((rec.p - center), (1.0/radius));
            rec.mat_ptr = mat_ptr;
            return true;
        }

        temp = (-b + sqrt(discriminant)) / (2.0*a);
        if (temp < t_max && temp > t_min) //if t is within desired interval
        {
            rec.t = temp;
            rec.p = r.point_at_t(temp);
            rec.normal = vec3::scale((rec.p - center), (1.0/radius));
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }

    //no hit
    return false;
}

#endif