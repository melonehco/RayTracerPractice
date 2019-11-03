/* hitable_list.h
 * Defines the hitable_list class, which encapsulates finding
 * the closest hitable object a ray hits
 * based on the ray-tracing tutorial at https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf
 * 
 * Melody Mao
 * Fall 2019
 */

#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitable_list: public hitable
{
    public:
        hitable_list() {}
        hitable_list(hitable **l, int n) { list = l; list_size = n; }
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

        hitable **list;
        int list_size;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;

    //for each hitable obj in list
    for (int i = 0; i < list_size; i++)
    {
        //if this obj hits at a closer distance
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif