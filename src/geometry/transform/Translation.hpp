#pragma once

#include "../Object.hpp"
#include "../BoundingBox.hpp"

class Translation : public Object {
public:
    /**
     * construct a Translation object from original object
     * @param _object the object need to be translation
     * @param displacement the displacement of object which need.
    */
    Translation(std::shared_ptr<Object> _object, const tinyMath::vec3f& displacement)
        :object(_object), offset(displacement){}
    ~Translation(){}

    virtual std::optional<IntersectResult> intersect(const Ray& ray, float t_min, float t_max) const override {
        Ray moved_ray(ray.o - offset, ray.d, ray.time);
        auto r = object->intersect(moved_ray, t_min, t_max);
        if(r.has_value()) {
            IntersectResult res = r.value();
            res.coords += offset;
            res.setFrontFace(moved_ray, res.normal);
            return res;
        } else {
            return std::nullopt;
        }
    }

    virtual BoundingBox getBoundingBox(float time0, float time1) const override {
        auto oldBox = object->getBoundingBox(time0, time1);
        return BoundingBox(
            oldBox.min + offset,
            oldBox.max + offset
        );
    }
private:
    std::shared_ptr<Object> object;
    tinyMath::vec3f offset;
};