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
#include "material/Material.hpp"
#include "material/Diffuse.hpp"
#include "material/Metal.hpp"
#include "material/Dielectric.hpp"

int main() {
    int width = 400;
    float aspect_ratio = 16.0f / 9.0f;
    std::string filepath = "./result.ppm";
    std::shared_ptr<Image> image = std::make_shared<Image>(width, aspect_ratio, filepath);
    Camera camera(aspect_ratio);
    
    std::shared_ptr<Material> mat_ground = std::make_shared<Diffuse>(tinyMath::vec3f(0.8f, 0.8f, 0.0f));
    std::shared_ptr<Material> mat_center = std::make_shared<Diffuse>(tinyMath::vec3f(0.7f, 0.3f, 0.3f));
    std::shared_ptr<Material> mat_left = std::make_shared<Metal>(tinyMath::vec3f(0.8f), 0.3f);
    std::shared_ptr<Material> mat_right = std::make_shared<Metal>(tinyMath::vec3f(0.8f, 0.6f,0.2f), 1.0f);

    std::shared_ptr<Object> obj_ground = std::make_shared<Sphere>(tinyMath::vec3f(0.0f, -100.5f, -1.0f), 100.0f, mat_ground);
    std::shared_ptr<Object> obj_center = std::make_shared<Sphere>(tinyMath::vec3f(0.0f, 0.0f, -1.0f), 0.5f, mat_center);
    std::shared_ptr<Object> obj_left = std::make_shared<Sphere>(tinyMath::vec3f(-1.0f, 0.0f, -1.0f), 0.5f, mat_left);
    std::shared_ptr<Object> obj_right = std::make_shared<Sphere>(tinyMath::vec3f(1.0f, 0.0f, -1.0f), 0.5f, mat_right);
    
    Scene scene;
    scene.addObject(obj_ground);
    scene.addObject(obj_center);
    scene.addObject(obj_left);
    scene.addObject(obj_right);
    
    Renderer render(image);
    auto begin = std::chrono::system_clock::now();
    render.render(scene, camera);
    auto end = std::chrono::system_clock::now();
    printTimeTook(begin, end, "Render");
    
    image->write();
    return 0;
}