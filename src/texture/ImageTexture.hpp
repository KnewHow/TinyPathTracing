#pragma once

#include <string>
#include <iostream>

#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class ImageTexture :public Texture {
public:
    ImageTexture(const std::string& imagePath)
        :width(0), height(0), bytes_per_scanline(0), data(nullptr)
    {
        int components_per_pixel = bytes_per_pixel;
        data = stbi_load(imagePath.c_str(), &width, &height, &components_per_pixel, components_per_pixel);
        if(data == nullptr) {
            std::cerr << "load image texture error, image path is: " << imagePath << std::endl;
            width = height = 0;
        }
        bytes_per_scanline = bytes_per_pixel * width;
    }

    ~ImageTexture(){
        delete[] data;
    }

    virtual tinyMath::vec3f value(float u, float v, const tinyMath::vec3f& point) const override {
        if(data == nullptr) {
            return tinyMath::vec3f(0, 1, 1);
        }

        u = clamp(u, 0, 1);
        v = 1.0f - clamp(v, 0, 1);

        int i = static_cast<int>(u * width);
        int j = static_cast<int>(v * height);

        if(i >= width) {
            i = width - 1;
        }

        if(j >= height) {
            j = height - 1;
        }

        const float color_scale = 1.0f / 255.0f;
        auto pixel = data + j * bytes_per_scanline + i * bytes_per_pixel;
        
        tinyMath::vec3f color = tinyMath::vec3f(pixel[0], pixel[1], pixel[2]);
        
        return color * color_scale;
    }

private:
    unsigned char* data;
    int width, height;
    int bytes_per_scanline;
    const static int bytes_per_pixel = 3;
};