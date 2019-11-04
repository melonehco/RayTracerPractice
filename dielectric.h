/* dielectric.h
 * Defines the dielectric class, a subclass of material
 * that defines scattering for dielectric (glass-like) materials
 * based on the ray-tracing tutorial at https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf
 * 
 * Melody Mao
 * Fall 2019
 */

#ifndef DIELECTRICH
#define DIELECTRICH

#include "material.h"

/* calculates refraction of v by n and returns whether the refraction occurred
 * returns the resulting refracted vector in refracted
 */
bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
{
    vec3 uv = vec3::unit_vector(v);
    float dt = vec3::dot(uv, n);
    float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1 - dt*dt);

    if (discriminant > 0)
    {
        refracted = vec3::scale( (uv - vec3::scale(n, dt)), ni_over_nt ) - vec3::scale(n, sqrt(discriminant));
        return true;
    }
    else
    {
        return false;
    }
}

/* Schlick's polynomial approximation for reflectivity that varies w/ angle
 * (eg windows at steep angles become mirrors)
 */
float schlick(float cos, float ref_idx)
{
    float r0 = (1.0-ref_idx) / (1.0+ref_idx);
    r0 = r0*r0;
    return r0 + (1.0-r0)*pow(1.0 - cos, 5);
}

class dielectric: public material
{
    public:
        dielectric(float ri) : refract_idx(ri) {}

        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
        {
            vec3 reflected = reflect(vec3::unit_vector(r_in.direction()), rec.normal);
            attenuation = vec3(1.0, 1.0, 1.0);
            vec3 outward_normal;
            float ni_over_nt;
            vec3 refracted;
            float reflect_prob;
            float cosine;

            if (vec3::dot(r_in.direction(), rec.normal) > 0)
            {
                outward_normal = -rec.normal;
                ni_over_nt = refract_idx;
                cosine = refract_idx * vec3::dot(r_in.direction(), rec.normal) / r_in.direction().length();
            }
            else
            {
                outward_normal = rec.normal;
                ni_over_nt = 1.0/refract_idx;
                cosine = - vec3::dot(r_in.direction(), rec.normal) / r_in.direction().length();
            }

            //check whether refraction found to set probability of reflecting
            if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
            {
                reflect_prob = schlick(cosine, refract_idx);
            }
            else
            {
                reflect_prob = 1.0;
            }

            //decide whether to reflect or not
            if (drand48() < reflect_prob)
            {
                scattered = ray(rec.p, reflected);
            }
            else
            {
                scattered = ray(rec.p, refracted);
            }

            return true;

            //reflect incoming ray about surface normal
            // vec3 reflected = vec3::reflect(vec3::unit_vector(r_in.direction()), rec.normal);
            // scattered = ray(rec.p, reflected + vec3::scale(random_in_unit_sphere(), fuzz));
            // attenuation = albedo;
            // return vec3::dot(scattered.direction(), rec.normal) > 0;
        }

        float refract_idx;
};

#endif