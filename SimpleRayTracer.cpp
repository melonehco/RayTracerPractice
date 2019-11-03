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

/* returns the color at the point intersected in the given world by the given ray
 */
vec3 color(const ray& r, hitable *world)
{
    hit_record rec;
    //vec3 sphere_center = vec3(0, 0, -1);

    // float t = hit_sphere(sphere_center, 0.5, r); //t of intersection along ray
    // if (t > 0.0) //if there is an intersection
    // {
    //     vec3 N = vec3::unit_vector(r.point_at_t(t) - sphere_center); //surface normal
    //     //map from [-1, 1] range to [0, 1]
    //     return vec3::scale(vec3(N.x() + 1, N.y() + 1, N.z() + 1), 0.5);
    // }

    //if intersection, color based on surface normal
    if (world->hit(r, 0.0, MAXFLOAT, rec))
    {
        return vec3::scale(vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1), 0.5);
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
            
            // float u = float(i) / float(width);
            // float v = float(j) / float(height);
            // ray r(origin, lower_left_corner + vec3::scale(horizontal, u) + vec3::scale(vertical, v));
            // vec3 col = color(r, world);
            
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}