#pragma once

#include <memory>

#include "geometry/Ray.hpp"
#include "Image.hpp"
#include "Scene.hpp"
#include "Camera.hpp"

class Renderer {
public:
    Renderer(std::shared_ptr<Image> _image)
        :image(_image){}

    void render(const Scene& scene, const Camera& camera) {
        int maxDepth = 8;
        std::atomic_int p = 0;
        #pragma omp parallel for
        for(int j = image->height - 1; j >= 0; j--) {
            for(int i = image->width - 1; i >= 0; i--) {
                 tinyMath::vec3f r = tinyMath::vec3f(0.0f);
                for(int k = 0; k < camera.samples_per_pixel; k++) {
                    float u = (float) (i + get_random_float()) / (image->width - 1);
                    float v = (float) (j + get_random_float()) / (image->height - 1);
                    r += scene.castRay(camera.getRay(u, v), maxDepth);
                }
                image->framebuff[j * image->width + i] = r / (float)camera.samples_per_pixel;
            }
            p++;
            updateProgress((float) p / image->height);
        }
    }

private:
    std::shared_ptr<Image> image;
};