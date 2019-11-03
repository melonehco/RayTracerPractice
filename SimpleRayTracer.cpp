/* SimpleRayTracer.cpp
 * Creates a simple ray-tracing setup with camera at (0,0,0)
 * Outputs an image with a vertical gradient
 * based on the ray-tracing tutorial at https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf
 * 
 * Melody Mao
 * Fall 2019
 */

#include <stdlib.h> //for drand48
#include <iostream>
#include "float.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"

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

/* returns the color at the point intersected in the given world by the given ray
 */
vec3 color(const ray& r, hitable *world)
{
    hit_record rec;

    //if intersection, color based on surface normal
    //min t is 0.001 to get rid of shadow acne (hits at t's very close to 0)
    if (world->hit(r, 0.001, MAXFLOAT, rec))
    {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return vec3::scale(color( ray(rec.p, target-rec.p), world ),
                           0.5);
    }

    //no intersection
    vec3 unit_direction = vec3::unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0); //how far along y
    return vec3::scale( vec3(1.0, 1.0, 1.0), (1.0-t) ) + vec3::scale( vec3(0.5, 0.7, 1.0), t);
    //linear interpolation (gradient) between white and blue
}

int main()
{
    int width = 200;
    int height = 100;
    int num_samples = 100;

    std::cout << "P3\n" << width << " " << height << "\n255\n";

    camera cam;

    hitable *list[2];
    list[0] = new sphere(vec3(0, 0, -1), 0.5); //TODO: what's the difference btw calling with and w/o new?
    list[1] = new sphere(vec3(0, -100.5, -1), 100); //basically the floor
    hitable *world = new hitable_list(list, 2);

    for (int j = height - 1; j >= 0; j--)
    {
        for (int i = 0; i < width; i++)
        {
            vec3 col(0, 0, 0);

            //average colors from samples across pixel
            for (int s = 0; s < num_samples; s++)
            {
                float u = float(i + drand48()) / float(width);
                float v = float(j + drand48()) / float(height);
                ray r = cam.get_ray(u, v);
                col += color(r, world);
            }
            col /= float(num_samples);
            col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) ); //gamma correction
            
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}