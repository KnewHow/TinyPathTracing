#pragma once

#include <vector>

#include "Object.hpp"
#include "BoundingBox.hpp"
#include "AxisAlignedRectangle.hpp"
#include "material/Material.hpp"
#include "accelerator/BVH.hpp"

/**
 * a axis-aligned box represented min and max point
*/
class AxisAlignedBox: public Object {
public:
    AxisAlignedBox(const tinyMath::vec3f& p0, const tinyMath::vec3f& p1, std::shared_ptr<Material> material){
        min = p0;
        max = p1;
        objects.push_back(std::make_shared<XYRectangle>(p0.x, p1.x, p0.y, p1.y, p0.z, material));
        objects.push_back(std::make_shared<XYRectangle>(p0.x, p1.x, p0.y, p1.y, p1.z, material));

        objects.push_back(std::make_shared<XZRectangle>(p0.x, p1.x, p0.z, p1.z, p0.y, material));
        objects.push_back(std::make_shared<XZRectangle>(p0.x, p1.x, p0.z, p1.z, p1.y, material));

        objects.push_back(std::make_shared<YZRectangle>(p0.y, p1.y, p0.z, p1.z, p0.x, material));
        objects.push_back(std::make_shared<YZRectangle>(p0.y, p1.y, p0.z, p1.z, p1.x, material));

        bvh = std::make_shared<BVHAccelerator>(objects, 0.0, 1.0);
    }
    ~AxisAlignedBox(){}

    virtual std::optional<IntersectResult> intersect(const Ray& ray, float t_min, float t_max) const override {
        return bvh->intersect(ray, t_min, t_max);
    }

    virtual BoundingBox getBoundingBox(float time0, float time1) const override {
        BoundingBox bbox(min, max);
        return bbox;
    }
    
    tinyMath::vec3f min;
    tinyMath::vec3f max;
private:
    std::vector<std::shared_ptr<Object>> objects;
    std::shared_ptr<BVHAccelerator> bvh;
};