#pragma once

#include <optional>

#include "Ray.hpp"


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
};