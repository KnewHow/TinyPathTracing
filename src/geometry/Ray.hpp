#ifndef __RAY_H__
#define __RAY_H__

#include <memory>

#include "Vector.hpp"
#include "Object.hpp"
#include "material/Material.hpp"

/**
 * define a ray with origin and direction
*/
struct Ray {
    Ray(const tinyMath::vec3f origin, const tinyMath::vec3f direction)
        :o(origin), d(direction)
    {
        
    }

    ~Ray(){}
    tinyMath::vec3f o;
    tinyMath::vec3f d;

};

/**
 * the ray intersect with object result
*/
struct Intersection {
    float t; // the ray is o + t * d, this is the t
    tinyMath::vec3f hitPoint; // the coordinates of hit point
    tinyMath::vec3f normal; // the normal of hitpoint
    std::shared_ptr<const Object> object; // which the object be intersected
    std::shared_ptr<const Material> material; // the material of hitpoint
};

#endif