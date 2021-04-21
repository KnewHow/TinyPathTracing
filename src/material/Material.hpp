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
     * What the light emited from this material. In some emitted material, for example: light source,
     * it will return some color it's emitting, otherwise, for general material, it's not emitting.
     * @param u the u coordinate in texture
     * @param v the v coordinate in texture
     * @param point the coordinate of hit point
     * @return the color the material emitted, in default, if return (0, 0, 0)
    */
    virtual tinyMath::vec3f emitted(float u, float v, const tinyMath::vec3f& point) const {
        return tinyMath::vec3f(0.0f);
    }
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