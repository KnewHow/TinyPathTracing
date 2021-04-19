#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "geometry/BoundingBox.hpp"
#include "geometry/Object.hpp"
#include "geometry/Ray.hpp"

struct BVHNode {
    BVHNode() {
        box = BoundingBox();
        left = nullptr;
        right = nullptr;
        object = nullptr;
    }

    BoundingBox box;
    std::shared_ptr<BVHNode> left;
    std::shared_ptr<BVHNode> right;
    std::shared_ptr<Object> object;
};

/**
 * BVH accelerator
*/
class BVHAccelerator {
public:
    /**
     * construct bhv accelerator with primitive object and two time
    */
    BVHAccelerator(
        const std::vector<std::shared_ptr<Object>>& objs, float time0, float time1) {
        root = recursiveBuild(objs, time0, time1);
    }
    
    std::optional<IntersectResult> intersect(const Ray& ray, float t_min, float t_max) {
        if(root == nullptr) {
            return std::nullopt;
        } else {
            return recursiveIntersect(root, ray, t_min, t_max);
        }
    };

    ~BVHAccelerator(){}

private:

    std::shared_ptr<BVHNode> recursiveBuild(std::vector<std::shared_ptr<Object>> objects, float time0, float time1) { // recursive build bvh 
        std::shared_ptr<BVHNode> node = std::make_shared<BVHNode>();
        
        if(objects.size() == 1) {
            node->left = node->right = nullptr;
            node->object = objects[0];
            node->box = node->object->getBoundingBox(time0, time1);
        } else if(objects.size() == 2) {
            node->left = recursiveBuild(std::vector<std::shared_ptr<Object>>{objects[0]},time0, time1);
            node->right = recursiveBuild(std::vector<std::shared_ptr<Object>>{objects[1]},time0, time1);
            node->box = node->left->box.combine(node->right->box);
        } else {
            BoundingBox bCenterBox;
            for(const auto& obj: objects) {
                bCenterBox = bCenterBox.combine(obj->getBoundingBox(time0, time1).getCenter()); // get maxinum bounding box from center
            }
            BoundingBox::AXIS axis = bCenterBox.getLongestAxis();
            switch (axis) // choose longest center bouding-box axis then split them into two sub tree
            {
            case BoundingBox::AXIS::X:
                std::sort(objects.begin(), objects.end(),[time0, time1](const auto o1, const auto o2){
                    return o1->getBoundingBox(time0, time1).getCenter().x < o2->getBoundingBox(time0, time1).getCenter().x;
                });
                break;
            
            case BoundingBox::AXIS::Y:
                std::sort(objects.begin(), objects.end(),[time0, time1](const auto o1, const auto o2){
                    return o1->getBoundingBox(time0, time1).getCenter().y < o2->getBoundingBox(time0, time1).getCenter().y;
                });
                break;
            
            case BoundingBox::AXIS::Z:
                std::sort(objects.begin(), objects.end(),[time0, time1](const auto o1, const auto o2){
                    return o1->getBoundingBox(time0, time1).getCenter().z < o2->getBoundingBox(time0, time1).getCenter().z;
                });
                break;
            }

            auto begin = objects.begin();
            auto mid = begin + (objects.size() / 2);
            auto end = objects.end();
            auto subLeft = std::vector<std::shared_ptr<Object>>(begin, mid);
            auto subRight = std::vector<std::shared_ptr<Object>>(mid, end);
            node->left = recursiveBuild(subLeft, time0, time1);
            node->right = recursiveBuild(subRight, time0, time1);
            node->box = node->left->box.combine(node->right->box);
        }

        return node;
    };


    std::optional<IntersectResult> recursiveIntersect(std::shared_ptr<BVHNode> node, const Ray& ray, float t_min, float t_max) {
        if(node == nullptr) {
            return std::nullopt;
        } else if(node->box.intersectWithRay(ray, t_min, t_max)) {
            if(node->left == nullptr && node->right == nullptr) {
                return node->object->intersect(ray, t_min, t_max);
            } else {
                auto leftR = recursiveIntersect(node->left, ray, t_min, t_max);
                auto rightR = recursiveIntersect(node->right, ray, t_min, t_max);
                if(leftR.has_value() && rightR.has_value()) {
                    return leftR.value().t < rightR.value().t ? leftR : rightR;
                } else if(leftR.has_value()) {
                    return leftR;
                } else if(rightR.has_value()) {
                    return rightR;
                }
            }
        }
        return std::nullopt;
    }

    std::shared_ptr<BVHNode> root;
};