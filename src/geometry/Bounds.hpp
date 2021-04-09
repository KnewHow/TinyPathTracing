#ifndef __BOUNDS_H__
#define __BOUNDS_H__

#include <limits>

#include "Vector.hpp"

/**
 * this is bounding box, in this case, we just use AABB
*/
struct Bounds {
    Bounds(const tinyMath::vec3f& a, const tinyMath::vec3f& b) {
        for(int i = 0; i < 3; i++) {
            min[i] = std::min(a[i], b[i]);
            max[i] = std::max(a[i], b[i]);
        }
    }
    
    Bounds() {
        min = tinyMath::vec3f(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
        max = tinyMath::vec3f(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
    }
    ~Bounds(){};

    Bounds merge(const Bounds& other) {
        Bounds res;
        for(int i = 0; i < 3; i++) {
            res.min[i] = std::min(min[i], other.min[i]);
            res.max[i] = std::max(max[i], other.max[i]);
        }
        return res;
    }

    Bounds merge(const tinyMath::vec3f& v) {
        Bounds res;
        for(int i = 0; i < 3; i++) {
            res.min[i] = std::min(min[i], v[i]);
            res.max[i] = std::max(max[i], v[i]);
        }
        return res;
    }

    tinyMath::vec3f min;
    tinyMath::vec3f max;
};

#endif