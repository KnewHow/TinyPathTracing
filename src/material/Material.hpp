#pragma once

#include "Vector.hpp"

class Ray;
class IntersectResult;

/**
 * a material base class
*/

class Material {
public:
    /**
     * scatter a ray from current hit point according by material
     * @param ray the incident ray 
     * @param intersect the intersect information of current incident ray intersect with current object
     * @param attenuation the attenuation of color, it will be return
     * @param scattered the scatered ray calculated from this method
     * @return whether the intersect point has a scattered ray
    */
    virtual bool scatter(
        const Ray& ray, 
        const IntersectResult& intersect,
        tinyMath::vec3f& attenuation,
        Ray& scattered
    ) const = 0;
};