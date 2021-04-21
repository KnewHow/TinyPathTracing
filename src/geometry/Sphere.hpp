#pragma once

#include <tuple>
#include <cmath>

#include "Object.hpp"
#include "material/Material.hpp"
#include "BoundingBox.hpp"

class Sphere: public Object {
public:
    const tinyMath::vec3f center;
    const float radius;
    const std::shared_ptr<Material> material;
    BoundingBox bbox;

    Sphere(const tinyMath::vec3f& _center, const float& _radius, const std::shared_ptr<Material> _material)
        :center(_center), radius(_radius), material(_material) 
    {
        bbox = BoundingBox(
            center - tinyMath::vec3f(radius),
            center + tinyMath::vec3f(radius)
        );
    }
    
    virtual std::optional<IntersectResult> intersect(const Ray& ray, float t_min, float t_max) const override {
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
        
        tinyMath::vec3f hitPoint = ray.at(t);
        tinyMath::vec3f normal = ((hitPoint - center) / radius).normalize();
        auto uv = getUV(normal);
        IntersectResult r;
        r.t = t;
        r.coords = hitPoint;
        r.setFrontFace(ray, normal);
        r.material = this->material;
        r.u = std::get<0>(uv);
        r.v = std::get<1>(uv);
        return r;
    }

    virtual BoundingBox getBoundingBox(float time0, float time1) const override {
        return bbox;
    }
private:
    std::tuple<float, float> getUV(const tinyMath::vec3f& normal) const {
        float theta = std::acos(-normal.y);
        float phi = std::atan2(-normal.z, normal.x) + M_PI;
        float u = phi / (2 * M_PI);
        float v = theta / M_PI;
        return std::make_tuple(u, v);
    }
};