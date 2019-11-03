/* metal.h
 * Defines the metal class, a subclass of material
 * that defines scattering for metal (reflective) materials
 * based on the ray-tracing tutorial at https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf
 * 
 * Melody Mao
 * Fall 2019
 */

#ifndef METALH
#define METALH

#include "material.h"

class metal: public material
{
    public:
        metal(const vec3& a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }

        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
        {
            //reflect incoming ray about surface normal
            vec3 reflected = vec3::reflect(vec3::unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected + vec3::scale(random_in_unit_sphere(), fuzz));
            attenuation = albedo;
            return vec3::dot(scattered.direction(), rec.normal) > 0;
        }

        vec3 albedo;
        float fuzz; //how fuzzy reflections are, in range [0, 1)
};

#endif