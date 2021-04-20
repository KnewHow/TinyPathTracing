#pragma once


#include "Texture.hpp"
#include "noise/PerlinNoise.hpp"

class NoiseTexture: public Texture {
public:
    NoiseTexture(){
        noise = std::make_shared<PerlinNoise>();
        scale = 1.0f;
    }
    NoiseTexture(float _scale) {
        noise = std::make_shared<PerlinNoise>();
        scale = _scale;
    }
    ~NoiseTexture(){}
    
    virtual tinyMath::vec3f value(float u, float v, const tinyMath::vec3f& point) const override {
        return tinyMath::vec3f(1.0f) * noise->noise(scale * point);
    }

private:
    std::shared_ptr<PerlinNoise> noise;
    float scale;
};