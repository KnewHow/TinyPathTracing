#pragma once

#include <memory>

#include "Material.hpp"
#include "texture/Texture.hpp"
#include "texture/SolidColor.hpp"

class Isotropic: public Material {
public:
    Isotropic(const tinyMath::vec3f& color)
        :texture(std::make_shared<SolidColor>(color)){}
    Isotropic(const std::shared_ptr<Texture> _texture)
        :texture(_texture){}
    ~Isotropic(){}
    virtual bool scatter(
        const Ray& ray, 
        const IntersectResult& intersect,
        tinyMath::vec3f& attenuation,
        Ray& scattered
    ) const {
        scattered = Ray(intersect.coords, get_random_vector_in_unit_sphere().normalize(), ray.time);
        attenuation = texture->value(intersect.u, intersect.v, intersect.coords);
        return true;
    }

private:
    std::shared_ptr<Texture> texture;
};