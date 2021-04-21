#pragma once

#include <fstream>
#include <vector>

#include "Vector.hpp"
#include <common/Tools.hpp>

struct Image {
    const int width, height;
    const std::string filepath;
    const float aspect_ratio;
    std::vector<tinyMath::vec3f> framebuff;
    
    Image(int _width, int _height, const std::string& _filepath)
        :width(_width), height(_height), aspect_ratio((float)width / height), filepath(_filepath)
    {
        framebuff.resize(width * height);
    }

    Image(int _width, float _aspect_ratio, const std::string& _filepath)
        :width(_width), height((int)(_width / _aspect_ratio)), aspect_ratio(_aspect_ratio), filepath(_filepath)
    {
        framebuff.resize(width * height);
    }

    void write() const { // TODO optimize: let writing more effective
        

        std::ofstream fo;
        fo.open(filepath);
        fo << "P3\n"  << width << " " << height << "\n255\n";
        for(int j = height - 1; j>=0; j--) {
            for(int i = 0; i < width; i++) {
                int idx = j * width + i;
                tinyMath::vec3f rgb = framebuff[idx];
                int r = static_cast<int>(clamp(std::sqrt(rgb.x), 0.0f, 0.999) * 256.0f); // gamma correction
                int g = static_cast<int>(clamp(std::sqrt(rgb.y), 0.0f, 0.999) * 256.0f);
                int b = static_cast<int>(clamp(std::sqrt(rgb.z), 0.0f, 0.999) * 256.0f);
                fo << r << " " << g << " " << b << std::endl;
            }
        }
        fo.close();
    }
};