#pragma once

#include <memory>

#include "Material.hpp"
#include "texture/Texture.hpp"
#include "texture/SolidColor.hpp"

class DiffuseLight: public  Material{
public:
    DiffuseLight(const std::shared_ptr<Texture> _texture)
        :texture(_texture){}
    DiffuseLight(const tinyMath::vec3f& color)
        :texture(std::make_shared<SolidColor>(color)){}
    
    ~DiffuseLight(){}
    
    virtual tinyMath::vec3f emitted(float u, float v, const tinyMath::vec3f& point) const override {
        return texture->value(u, v, point);
    }
    
    virtual bool scatter(
        const Ray& ray, 
        const IntersectResult& intersect,
        tinyMath::vec3f& attenuation,
        Ray& scattered
    ) const override 
    {
        return false;
    }
private:
    std::shared_ptr<Texture> texture;
};