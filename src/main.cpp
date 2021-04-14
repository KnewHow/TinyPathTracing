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
#include "geometry/Sphere.hpp"

int main() {
    int width = 400;
    float aspect_ratio = 16.0f / 9.0f;
    std::string filepath = "./result.ppm";
    std::shared_ptr<Image> image = std::make_shared<Image>(width, aspect_ratio, filepath);
    Camera camera(aspect_ratio);
    Scene scene;
    scene.addObject(std::make_shared<Sphere>(tinyMath::vec3f(0, 0, -1.0f), 0.5f));
    scene.addObject(std::make_shared<Sphere>(tinyMath::vec3f(0.0f, -100.5f,-1.0f), 100.0f));
    Renderer render(image);
    
    auto begin = std::chrono::system_clock::now();
    render.render(scene, camera);
    auto end = std::chrono::system_clock::now();
    printTimeTook(begin, end, "Render");
    image->write();
    return 0;
}