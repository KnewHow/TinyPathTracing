#pragma once


#include <vector>
#include <memory>

#include "Object.hpp"
#include "BoundingBox.hpp"
#include "accelerator/BVH.hpp"

/**
 * a group objects
*/
class ObjectGroup: public Object {
public:
    ObjectGroup()
        :bbox(), objects(), bvh(nullptr){}
    ~ObjectGroup(){}
    void addObject(std::shared_ptr<Object> object) {
        objects.push_back(object);
    }

    void buildBVH() {
        if(objects.empty()) {
            std::cout << "Object groups is empty, build BVH failed!\n";
        } else {
            bvh = std::make_shared<BVHAccelerator>(objects, 0, 1);
            buildInnerBoundingBox();
        }
    }

    virtual std::optional<IntersectResult> intersect(const Ray& ray, float t_min, float t_max) const override {
        return bvh->intersect(ray, t_min, t_max);
    }

    virtual BoundingBox getBoundingBox(float time0, float time1) const override {
        if(std::fabs(time0 - 0) < 1e-6 && std::fabs(time1 - 1) < 1e-6) {
            return bbox; // if not motion blur, use calculated bbox to accelerate
        }
        BoundingBox box;
        for(auto& object: objects) {
            box = box.combine(object->getBoundingBox(time0, time1));
        }
        return box;
    }



private:
    void buildInnerBoundingBox() {
        for(auto& object: objects) {
            bbox = bbox.combine(object->getBoundingBox(0, 1));
        }
    }
    std::vector<std::shared_ptr<Object>> objects;
    std::shared_ptr<BVHAccelerator> bvh;
    BoundingBox bbox;
};