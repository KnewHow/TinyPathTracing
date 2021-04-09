#ifndef __BOUNDS_H__
#define __BOUNDS_H__

#include <limits>

#include "Vector.hpp"

/**
 * this is bounding box, in this case, we just use AABB
*/
class Bounds {

public:
    Bounds(const tinyMath::vec3f& a, const tinyMath::vec3f& b)
        :min(a), max(b){}
    Bounds() {
        min = tinyMath::vec3f(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
        max = tinyMath::vec3f(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
    }
    ~Bounds(){};
private:
    tinyMath::vec3f min;
    tinyMath::vec3f max;
};

#endif