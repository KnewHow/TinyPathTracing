#pragma once

#include "Object.hpp"

class Sphere: public Object {
public:
    const tinyMath::vec3f center;
    const float radius;
    Sphere(const tinyMath::vec3f& _center, const float& _radius)
        :center(_center), radius(_radius){}
    
    virtual std::optional<IntersectResult> intersect(const Ray& ray, float t_min, float t_max) override {
        tinyMath::vec3f L = center - ray.o;
        float tca = tinyMath::dotProduct(L, ray.d);
        float d2 = tinyMath::dotProduct(L, L) - tca * tca;
        if(d2 > radius * radius) 
            return std::nullopt;
        float thc = sqrtf(radius * radius - d2);
        float t = tca - thc;
        float t1 = tca + thc;
        if(t > t_max || t < t_min)
            t = t1;
        if(t > t_max || t < t_min) 
            return std::nullopt;
        
        tinyMath::vec3f hitPoint = ray.o + t * ray.d;
        tinyMath::vec3f normal = (hitPoint - center).normalize();
        IntersectResult r;
        r.t = t;
        r.coords = hitPoint;
        r.setFrontFace(ray, normal);
        return r;
    }
};