#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    //public functions for ray class.
    public:
        ray() {}
        //constructor.
        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}
        //return origin point.
        const point3& origin() const { return orig; }
        //return direction of ray.
        const vec3& direction() const { return dir; }
        //return next point along the ray.
        point3 at(double t) const {
            return orig + t * dir;
        }
    //private member variables for ray class.
    private:
        point3 orig;
        vec3 dir;
};

#endif