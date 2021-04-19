#pragma once

#include <memory>

#include "Object.hpp"
#include "Ray.hpp"
#include "material/Material.hpp"
#include "BoundingBox.hpp"

class MovingSphere: public Object {
public:
    const tinyMath::vec3f center0, center1; // the center when shpere moving from center0 to center1
    const float time0, time1; // the time when shpere moving from center0 to center1
    const float radius;
    const std::shared_ptr<Material> material;

    /**
     * constructor of MovingSphere
     * the param is correspond of above
    */
    MovingSphere(
        const tinyMath::vec3f& _center0, 
        const tinyMath::vec3f& _center1, 
        const float _time0, 
        const float _time1, 
        const float _radius, 
        const std::shared_ptr<Material> _material)
            :center0(_center0), center1(_center1), time0(_time0), time1(_time1), radius(_radius), material(_material){}

    ~MovingSphere(){}

    tinyMath::vec3f center(float time) {
        return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
    }

    virtual std::optional<IntersectResult> intersect(const Ray& ray, float t_min, float t_max) {
        tinyMath::vec3f L = center(ray.time) - ray.o;
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
        tinyMath::vec3f normal = ((hitPoint - center(ray.time)) / radius).normalize();
        IntersectResult r;
        r.t = t;
        r.coords = hitPoint;
        r.setFrontFace(ray, normal);
        r.material = this->material;
        return r;
    }

    virtual BoundingBox getBoundingBox(float time0, float time1) override {
        BoundingBox bbox0 = BoundingBox(
            center(time0) - tinyMath::vec3f(radius),
            center(time0) + tinyMath::vec3f(radius)
        );

        BoundingBox bbox1 = BoundingBox(
            center(time1) - tinyMath::vec3f(radius),
            center(time1) + tinyMath::vec3f(radius)
        );
        return bbox0.combine(bbox1);
    }

};