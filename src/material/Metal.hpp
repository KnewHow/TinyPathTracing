#pragma once

#include "Material.hpp"
#include "geometry/Ray.hpp"
#include "common/Tools.hpp"

class Metal: public Material {
public:
    Metal(const tinyMath::vec3f color)
        :albedo(color){}
    ~Metal(){}
    virtual bool scatter(
        const Ray& ray, 
        const IntersectResult& intersect,
        tinyMath::vec3f& attenuation,
        Ray& scattered
    ) const override
    {
        // tinyMath::vec3f reflectDir = reflect(ray.d.normalize(), intersect.normal).normalize();
        // scattered = Ray(intersect.coords, reflectDir);
        // attenuation = albedo;
        // return tinyMath::dotProduct(reflectDir, intersect.normal) > 0.0f;
    }

    const tinyMath::vec3f albedo;
};