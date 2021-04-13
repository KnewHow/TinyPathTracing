#include <iostream>
#include <memory>
#include <atomic>
#include <thread>
#include <chrono>

#include "Vector.hpp"
#include "Image.hpp"
#include "common/Tools.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"

int main() {
    int width = 400;
    float aspect_ratio = 16.0f / 9.0f;
    std::string filepath = "./result.ppm";
    std::shared_ptr<Image> image = std::make_shared<Image>(width, aspect_ratio, filepath);
    Scene scene;
    Renderer render(image);
    render.render(scene);
    image->write();
    return 0;
}