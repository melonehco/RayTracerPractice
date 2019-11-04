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
#include <fstream>
#include "float.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

/* returns the color at the point intersected in the given world by the given ray
 * runs recursively for scattering rays; depth indicates recursion depth
 */
vec3 color(const ray& r, hitable *world, int depth)
{
    hit_record rec;

    //if intersection, color based on surface normal
    //min t is 0.001 to get rid of shadow acne (hits at t's very close to 0)
    if (world->hit(r, 0.001, MAXFLOAT, rec))
    {
        ray scattered;
        vec3 attenuation;

        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            //std::cout << "calling color recursively\n";
            return attenuation * color(scattered, world, depth+1);
        }
        else
        {
            return vec3(0, 0, 0);
        }
    }

    //no intersection
    vec3 unit_direction = vec3::unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0); //how far along y
    return vec3::scale( vec3(1.0, 1.0, 1.0), (1.0-t) ) + vec3::scale( vec3(0.5, 0.7, 1.0), t);
    //linear interpolation (gradient) between white and blue
}

int main(int argc, char **argv)
{
    int width = 200;
    int height = 100;
    int num_samples = 100;

    std::ofstream imgfile;
    if (argc > 1)
    {
        imgfile.open ( argv[1] );
    }
    else
    {
        imgfile.open ("ray-trace-out.ppm");
    }
    imgfile << "P3\n" << width << " " << height << "\n255\n";

    vec3 lookfrom(3, 3, 2);
    vec3 lookat(0, 0, -1);
    float dist_to_focus = (lookat - lookfrom).length();
    float aperture = 2.0;
    //         look from, look at, vup          vfov, aspect ratio
    camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(width)/float(height), aperture, dist_to_focus);

    hitable *list[4];
    //TODO: what's the difference btw calling with and w/o new?
    //----------------------version up to ch 9
    list[0] = new sphere( vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)) );
    list[1] = new sphere( vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)) ); //basically the floor
    list[2] = new sphere( vec3(1, 0, -1), 0.5, new dielectric(1.5) );
    //list[3] = new sphere( vec3(1, 0, -1), -0.45, new dielectric(1.5) ); //inner sphere for bubble
    list[3] = new sphere( vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8), 0.2) );
    //----------------------version for ch 10 pt 1
    // float R = cos(M_PI/4.0);
    // list[0] = new sphere( vec3(-R, 0, -1), R, new lambertian(vec3(0, 0, 1)) );
    // list[1] = new sphere( vec3(R, 0, -1), R, new lambertian(vec3(1, 0, 0)) );
    //----------------------
    hitable *world = new hitable_list(list, 4);

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
                col += color(r, world, 0);
            }
            col /= float(num_samples);
            col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) ); //gamma correction
            
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            
            imgfile << ir << " " << ig << " " << ib << "\n";
        }
    }

    imgfile.close();
}