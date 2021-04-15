#pragma once

#include "Material.hpp"
#include "geometry/Ray.hpp"

class Diffuse: public Material {
public:
    Diffuse(const tinyMath::vec3f& color)
        :albedo(color){}
    ~Diffuse(){}
    virtual bool scatter(
        const Ray& ray, 
        const IntersectResult& intersect,
        tinyMath::vec3f& attenuation,
        Ray& scattered
    ) const override
    {
        tinyMath::vec3f dir = (intersect.coords + intersect.normal + get_random_vector_in_unit_sphere().normalize() - intersect.coords).normalize();
        if(isNearZero(dir)) {
            dir = intersect.normal;
        }
        scattered = Ray(intersect.coords, dir);
        attenuation = albedo;
        return true;
    }

private:
    const tinyMath::vec3f albedo;
};