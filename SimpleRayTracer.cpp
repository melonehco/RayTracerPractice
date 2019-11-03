/* SimpleRayTracer.cpp
 * Creates a simple ray-tracing setup with camera at (0,0,0)
 * Outputs an image with a vertical gradient
 * based on the ray-tracing tutorial at https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf
 * 
 * Melody Mao
 * Fall 2019
 */

#include <iostream>
#include "ray.h"

//returns the color at the point intersected by the given ray
vec3 color(const ray& r)
{
    vec3 unit_direction = vec3::unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0); //how far along y
    return vec3::scale( vec3(1.0, 1.0, 1.0), (1.0-t) ) + vec3::scale( vec3(0.5, 0.7, 1.0), t);
    //linear interpolation between white and blue
}

int main()
{
    int width = 200;
    int height = 100;
    std::cout << "P3\n" << width << " " << height << "\n255\n";
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0); //TODO: why is this one 4?
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    for (int j = height - 1; j >= 0; j--)
    {
        for (int i = 0; i < width; i++)
        {
            float u = float(i) / float(width);
            float v = float(j) / float(height);
            ray r(origin, lower_left_corner + vec3::scale(horizontal, u) + vec3::scale(vertical, v));
            vec3 col = color(r);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}