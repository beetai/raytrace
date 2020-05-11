#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <vector>
#include <memory>

using std::shared_ptr;
using std::make_shared;

class hittable_list: public hittable {
    public:
        hittable_list() {};
        hittable_list(shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<hittable> object) { objects.push_back(object); }

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;

    public:
        std::vector<shared_ptr<hittable>> objects;
};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closestsf = t_max;

    /*
     * for each object
     *     if ray hits object
     *         set hit_anything to true
     *         update closestsf to t of local hit record
     *         set return hit record (rec) to local hit record
     */
    for (const auto& object : objects) {
        if (object->hit(r, t_min, closestsf, temp_rec)) {
            hit_anything = true;
            closestsf = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif /* HITTABLE_LIST_H */
