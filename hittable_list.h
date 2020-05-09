#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <vector>
#include <memory>

using std::shared_ptr;
using std::make_shared;

class hittableList: public hittable {
    public:
        hittableList() {};
        hittableList(shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<hittable> object) { objects.push_back(object); }

        virtual bool hit(const ray& r, double t_min, double t_max, hitRecord& rec) const;

    public:
        std::vector<shared_ptr<hittable>> objects;
};

bool hittableList::hit(const ray& r, double t_min, double t_max, hitRecord& rec) const {
    hitRecord tempRec;
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
        if (object->hit(r, t_min, closestsf, tempRec)) {
            hit_anything = true;
            closestsf = tempRec.t;
            rec = tempRec;
        }
    }

    return hit_anything;
}

#endif /* HITTABLE_LIST_H */
