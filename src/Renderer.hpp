#pragma once

#include <memory>

#include "geometry/Ray.hpp"
#include "Image.hpp"
#include "Scene.hpp"

class Renderer {
public:
    Renderer(std::shared_ptr<Image> _image)
        :image(_image)
    {   
        origin = tinyMath::vec3f(0.0f, 0.0f, 0.0f);
        viewport_width = viewport_height * image->aspect_ratio;
        horizontal = tinyMath::vec3f(viewport_width, 0.0f, 0.0f);
        vertical = tinyMath::vec3f(0.0f, viewport_height, 0.0f);
        lower_left_corner = origin - (horizontal / 2.0) - (vertical / 2.0) - tinyMath::vec3f(0.0, 0.0, focal_length); // let standard square equal ratio with image
    }

    void render(const Scene& scene) {
        std::atomic_int p = 0;
        
        for(int j = image->height - 1; j >= 0; j--) {
            for(int i = image->width - 1; i >= 0; i--) {
                int u = (float) i / (image->width - 1);
                int v = (float) j / (image->height - 1);
                tinyMath::vec3f d = (lower_left_corner + u * horizontal + v * vertical - origin).normalize();
                Ray ray(origin, d);
                image->framebuff[j * image->width + i] = scene.castRay(ray);
            }
            p++;
            updateProgress((float) p / image->height);
        }
    }

private:
    std::shared_ptr<Image> image;
    const float viewport_height = 2.0;
    float viewport_width = viewport_height * (16.0 / 9.0);
    const float focal_length = 1.0f;
    tinyMath::vec3f origin;
    tinyMath::vec3f horizontal;
    tinyMath::vec3f vertical;
    tinyMath::vec3f lower_left_corner;
};