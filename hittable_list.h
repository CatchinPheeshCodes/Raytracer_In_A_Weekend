#ifndef HITTABLE_LIST
#define HITTABLE_LIST

#include "rtweekend.h"
#include "hittable.h"
#include <vector>

//class to store list of hittable objects.
class hittable_list : public hittable {
    public:
        std::vector<shared_ptr<hittable>> objects;

        hittable_list() {}
        hittable_list(shared_ptr<hittable> object) {add(object);}
        //clear objects vector.
        void clear() { objects.clear();}

        //add hittable to objects vector.
        void add(shared_ptr<hittable> object) {
            objects.push_back(object);
        }

        bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
            //initializations.
            hit_record temp_rec;
            bool hit_anything = false;
            auto closest_so_far = ray_tmax;

            //setter. if object hits, update variables.
            for(const auto & object : objects) {
                if(object->hit(r, ray_tmin, closest_so_far, temp_rec)) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }
            return hit_anything;
        }
};

#endif