#pragma once

#include <limits>

#include "Vector.hpp"
#include "Ray.hpp"

/**
 * A Axis-Aligned-Bounding-Box
*/
struct BoundingBox {

    enum class AXIS {
        X = 1,
        Y = 2,
        Z = 3
    };

    /**
     * construct a bounding box from two point.
    */
    BoundingBox(const tinyMath::vec3f& p0, const tinyMath::vec3f& p1) {
        min = tinyMath::vec3f(0.0f);
        max = tinyMath::vec3f(0.0f);
        for(int i = 0; i < 3; i++) {
            min[i] = std::min(p0[i], p1[i]);
            max[i] = std::max(p0[i], p1[i]);
        }
    }
    
    BoundingBox() {
        min = tinyMath::vec3f(std::numeric_limits<float>::infinity());
        max = tinyMath::vec3f(-std::numeric_limits<float>::infinity());
    }

    /**
     * combine a bouding box with another.
    */
    BoundingBox combine(const BoundingBox& other) const {
        BoundingBox res;
        for(int i = 0; i < 3; i++) {
            res.min[i] = std::min(min[i], other.min[i]);
            res.max[i] = std::max(max[i], other.max[i]);
        }
        return res;
    }

    /**
     * combine a bounding box with a point
    */
    BoundingBox combine(const tinyMath::vec3f& point) const {
        BoundingBox res;
        for(int i = 0; i < 3; i++) {
            res.min[i] = std::min(min[i], point[i]);
            res.max[i] = std::max(max[i], point[i]);
        }
        return res;
    }

    /**
     * get center point of bouning box
    */
    tinyMath::vec3f getCenter() {
        return (max + min) / 2.0f;
    }

    /**
     * get longest axis in bounding box
    */
    AXIS getLongestAxis() {
        tinyMath::vec3f d = max - min;
        if(d.x > d.y && d.x > d.z) {
            return AXIS::X;
        } else if(d.y > d.z) {
            return AXIS::Y;
        } else {
            return AXIS::Z;
        }
    }

    /**
     * Bounding box intersecting with ray
     * @param ray the ray with o + t * d
     * @param t_min the minimum value of t in hit point
     * @param t_max the maximum value of t in hit point
     * @return If the box intersect with ray, return true, otherwise return falses
     * 
    */
    bool intersectWithRay(const Ray& ray, float t_min, float t_max) {
        for(int i = 0; i < 3; i++) {
            float invDir = 1.0f / ray.d[i];
            float t0 = (min[i] - ray.o[i]) * invDir;
            float t1 = (max[i] - ray.o[i]) * invDir;
            if(invDir < 0) {
                std::swap(t0, t1);
            }
            t_min = std::max(t_min, t0);
            t_max = std::min(t_max, t1);
            if(t_max <= t_min) {
                return false;
            }
        }
        return true;
    }

    tinyMath::vec3f min;
    tinyMath::vec3f max;

};