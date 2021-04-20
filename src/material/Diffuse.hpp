#pragma once

#include "Material.hpp"
#include "geometry/Ray.hpp"
#include "texture/Texture.hpp"
#include "texture/SolidColor.hpp"

class Diffuse: public Material {
public:
    Diffuse(const tinyMath::vec3f& color)
        :texture(std::make_shared<SolidColor>(color)){}
    Diffuse(const std::shared_ptr<Texture> _texture)
        :texture(_texture){}
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
        scattered = Ray(intersect.coords, dir, ray.time);
        attenuation = texture->value(intersect.u, intersect.v, intersect.coords);
        return true;
    }

private:
    std::shared_ptr<Texture> texture;
};