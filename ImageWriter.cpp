/* ImageWriter.cpp
 * Writes an image out to a PPM file
 * based on the ray-tracing tutorial at https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf
 * 
 * Melody Mao
 * Fall 2019
 */

#include <iostream>
#include "vec3.h"

int main()
{
    int width = 200;
    int height = 100;
    std::cout << "P3\n" << width << " " << height << "\n255\n";
    for (int j = height - 1; j >= 0; j--)
    {
        for (int i = 0; i < width; i++)
        {
            vec3 col(float(i) / float(width),
                     float(j) / float(height),
                     0.2);
            // float r = float(i) / float(width);
            // float g = float(j) / float(height);
            // float b = 0.2;
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]); //why 255.99?
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    //TODO: write out to file
}