#pragma once

#include <memory>

#include "Texture.hpp"

/**
 * a checker texture
*/
class CheckerTexture: public Texture {
public:
    CheckerTexture(const std::shared_ptr<Texture> _odd, const std::shared_ptr<Texture> _even)
        :odd(_odd), even(_even){}
    CheckerTexture(const tinyMath::vec3f& odd_color, const tinyMath::vec3f& even_color)
        :odd(std::make_shared<SolidColor>(odd_color)), even(std::make_shared<SolidColor>(even_color)){}
    ~CheckerTexture(){}

    virtual tinyMath::vec3f value(float u, float v, const tinyMath::vec3f& point) const override {
        float sins = std::sin(10 * point.x) * std::sin(10 * point.y) * std::sin(10 * point.z);
        if(sins < 0) 
            return odd->value(u, v, point);
        else
            return even->value(u, v, point);
    }
    
private:
    std::shared_ptr<Texture> odd; // the odd checker texture
    std::shared_ptr<Texture> even; // the even checker texture
};