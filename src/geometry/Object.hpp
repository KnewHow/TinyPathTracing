#pragma once

#include <optional>

#include "Ray.hpp"

class BoundingBox;


class Object {
public:
    /**
     * Wheather the ray intersect with the object, if they are, and the t is between `t_min` and `t_max` return the intersect result, otherwise return the nullopt
     * @param ray the ray casting
     * @param t_min the floor of the t
     * @param t_max the upper of the t
     * @return if the ray intersectes with the object, return the intersect result, otherwise return nullopt 
    */
    virtual std::optional<IntersectResult> intersect(const Ray& ray, float t_min, float t_max) = 0;
    
    /**
     * Getting primitive geomerty bounding box. in this time, we add two timestamp to get moving object. 
     * If your object static, don't have to use them.
    */
    virtual BoundingBox getBoundingBox(float time0, float time1) = 0;
};