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
        area = 0.0f;
    }

    ~BVHNode(){}

    Bounds bounding;
    std::shared_ptr<BVHNode> left;
    std::shared_ptr<BVHNode> right;
    std::shared_ptr<Object> object;
    float area;
};

class BVH {
public:
    BVH(const std::vector<std::shared_ptr<Object>>& objs);
    ~BVH();
    /**
     * cast ray intersect with bvh
     * @param ray the ray
     * @return if they are intersecting, return intersection info, otherwise return nullopt
    */
    std::optional<Intersection> intersect(const Ray& ray) const;
    /**
     * sample in bvh
     * @param pos the sample position, it will be return to caller.
     * @param pdf the probability density function, it will be return to caller
    */
    void sample(Intersection& pos, float& pdf) const;
private:
    std::shared_ptr<BVHNode> recursiveBuild(std::vector<std::shared_ptr<Object>> objs) const;
    std::optional<Intersection> recursiveIntersect(const Ray& ray, std::shared_ptr<BVHNode> r) const;
    void recursiveSample(std::shared_ptr<BVHNode> r, float p, Intersection& pos, float& pdf) const;
    
    const std::vector<std::shared_ptr<Object>>& objects;
    std::shared_ptr<BVHNode> root;
};

#endif