/*
 *
 */

#include <iostream>

int main()
{
    int width = 200;
    int height = 100;
    std::cout << "P3\n" << width << " " << height << "\n255\n";
    for (int j = height - 1; j >= 0; j--)
    {
        for (int i = 0; i < width; i++)
        {
            float r = float(i) / float(width);
            float g = float(j) / float(height);
            float b = 0.2;
            int ir = int(255.99 * r);
            int ig = int(255.99 * g);
            int ib = int(255.99 * b); //why 255.99?
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    //TODO: write out to file
}