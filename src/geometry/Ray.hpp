#pragma once

#include "Vector.hpp"

/**
 * define a ray with o + t * d
*/
struct Ray
{
    Ray(const tinyMath::vec3f& origin, const tinyMath::vec3f& direction)
        :o(origin), d(direction){}
    
    const tinyMath::vec3f o;
    const tinyMath::vec3f d;
};
