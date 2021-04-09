#ifndef __BVH_H__
#define __BVH_H__


#include "geometry/Object.hpp"
#include "geometry/Ray.hpp"
#include "geometry/Bounds.hpp"

/**
 * A BVH accelerator, refer: http://www.pbr-book.org/3ed-2018/Primitives_and_Intersection_Acceleration/Bounding_Volume_Hierarchies.html#sec:sah
*/

struct BVHNode {
    BVHNode() {
        bounding = Bounds();
        left = nullptr;
        right = nullptr;
        object = nullptr;
    }

    ~BVHNode(){}

    Bounds bounding;
    std::shared_ptr<BVHNode> left;
    std::shared_ptr<BVHNode> right;
    std::shared_ptr<Object> object;
};

class BVH {
public:
    BVH(const std::vector<std::shared_ptr<Object>>& objs);
    ~BVH();
    std::optional<Intersection> intersect(const Ray& ray) const;
private:
    std::shared_ptr<BVHNode> recursiveBuild(std::vector<std::shared_ptr<Object>> objs) const;
    std::optional<Intersection> recursiveIntersect(const Ray& ray, std::shared_ptr<BVHNode> r) const;
    const std::vector<std::shared_ptr<Object>>& objects;
    std::shared_ptr<BVHNode> root;
};

#endif