#ifndef HITLIST
#define HITLIST

#include "hittable.h"
#include "memory"
#include "vector"


// Effectively providing a scene representation, but needs to be replaced with BVH later
class HittableList : public Hittable {

    std::vector<shared_ptr<Hittable>> hitList;

    public:

        HittableList() {}
        HittableList(shared_ptr<Hittable> obj) { add(obj);}
        
        void clear() { hitList.clear(); }
        void add(shared_ptr<Hittable> obj) { hitList.push_back(obj); }
        
        virtual bool hit(const Ray& ray, Interval ray_t, HitRecord& record) const override{
            HitRecord tmp_rec;
            bool hit_obj = false;
            double t_closest = ray_t.max;

            
            for (const auto& object: hitList){
                if (object->hit(ray, Interval(ray_t.min, t_closest), tmp_rec)){
                    hit_obj = true;
                    t_closest = tmp_rec.t;
                    record = tmp_rec;
                }
            }

            return hit_obj;
        }




};


#endif

