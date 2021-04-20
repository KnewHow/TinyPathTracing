#pragma once

#include <memory>

#include "Texture.hpp"

class SolidColor: public Texture {
public:
    SolidColor(){};
    SolidColor(const tinyMath::vec3f _color)
        :color(_color){}
    SolidColor(float red, float green, float blue)
        :color(tinyMath::vec3f(red, green, blue)){}

    virtual tinyMath::vec3f value(float u, float v, const tinyMath::vec3f& point) const override {
        return color;
    }

    ~SolidColor(){};

private:
    tinyMath::vec3f color;
};