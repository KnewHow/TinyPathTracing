#ifndef __BOUNDS_H__
#define __BOUNDS_H__

#include "Vector.hpp"

/**
 * this is bounding box, in this case, we just use AABB
*/
class Bounds {

public:
    Bounds();
    ~Bounds();
private:
    tinyMath::vec3f min;
    tinyMath::vec3f max;
};

#endif