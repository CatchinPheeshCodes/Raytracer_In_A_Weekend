#ifndef HITTABLE_H
#define HITTABLE_H
#include "ray.h"

//defining structure to store information about a hittable object.
class hit_record {
    public:
        // intersection point.
        point3 p;
        //surface normal vector at the intersection point.
        vec3 normal;
        //distance along the ray where the hit occurred.
        double t;

};

class hittable {
    public:
        //destructor.
        virtual ~hittable() = default;
        //testing if ray hits the object.
        virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};

#endif