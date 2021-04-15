#pragma once

#include "Material.hpp"
#include "geometry/Ray.hpp"
#include "common/Tools.hpp"

class Metal: public Material {
public:
    Metal(const tinyMath::vec3f color, float _fuzz = 0.0f)
        :albedo(color), fuzz(_fuzz){}
    ~Metal(){}
    virtual bool scatter(
        const Ray& ray, 
        const IntersectResult& intersect,
        tinyMath::vec3f& attenuation,
        Ray& scattered
    ) const override
    {
        tinyMath::vec3f reflectDir = reflect(ray.d.normalize(), intersect.normal);
        reflectDir = (reflectDir +  fuzz * get_random_vector_in_unit_sphere()).normalize();
        scattered = Ray(intersect.coords, reflectDir);
        attenuation = albedo;
        return tinyMath::dotProduct(reflectDir, intersect.normal) > 0.0f;
    }
private:
    const tinyMath::vec3f albedo;
    float fuzz;
};