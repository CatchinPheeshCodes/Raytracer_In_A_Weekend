#ifndef SPHERE_H
#define SPHERE_H

#include "rtweekend.h"
#include "hittable.h"

class sphere : public hittable {
    public:
        sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {
            //TO DO: Initialize the material pointer as 'mat'.
        }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            vec3 orig_c = center - r.origin();
            auto a = r.direction().length_squared();
            auto h = dot(r.direction(), orig_c);
            auto c = orig_c.length_squared() - radius * radius;
            auto discriminant = h * h - a * c;

            if(discriminant < 0) {
                return false;
            }
            auto sqrt_d = std::sqrt(discriminant);

            //Find the nearest root in the acceptable range (-1, 1).
            auto root = (h - sqrt_d) / a;
            if(!ray_t.surrounds(root)) {
                root = (h + sqrt_d) / a;
                if(!ray_t.surrounds(root)) {
                    return false;
                }
            }
            //Update hit record variables. See hittable.h for t, p and normal.
            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;

            return true;
        }


    private:
        point3 center;
        double radius;
        shared_ptr<material> mat;    
};

#endif