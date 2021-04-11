#include <iostream>
#include <thread>
#include <chrono>

#include "Vector.hpp"
#include "common/Tools.hpp"
#include "material/Material.hpp"
#include "geometry/Sphere.hpp"
#include "geometry/Triangle.hpp"
#include "geometry/MeshTriangle.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"


int main() {
    int width = 784;
    int height = 784;
    Scene scene(width, height);
    
    std::shared_ptr<Material> red = std::make_shared<Material>(MaterialType::DIFFUSE, tinyMath::vec3f(0.0f, 0.0f,0.0f));
    red->setKd(tinyMath::vec3f(0.63f, 0.065f, 0.05f));
    std::shared_ptr<Material> green = std::make_shared<Material>(MaterialType::DIFFUSE, tinyMath::vec3f(0.0f, 0.0f,0.0f));
    green->setKd(tinyMath::vec3f(0.14f, 0.45f, 0.091f));
    std::shared_ptr<Material> white = std::make_shared<Material>(MaterialType::DIFFUSE, tinyMath::vec3f(0.0f, 0.0f,0.0f));
    white->setKd(tinyMath::vec3f(0.725f, 0.71f, 0.68f));
    std::shared_ptr<Material> light = std::make_shared<Material>(MaterialType::DIFFUSE, (8.0f * tinyMath::vec3f(0.747f+0.058f, 0.747f+0.258f, 0.747f) + 15.6f * tinyMath::vec3f(0.740f+0.287f,0.740f+0.160f,0.740f) + 18.4f *tinyMath::vec3f(0.737f+0.642f,0.737f+0.159f,0.737f)));
    light->setKd(tinyMath::vec3f(0.65f, 0.65f, 0.65f));

    std::shared_ptr<MeshTriangle> floor = std::make_shared<MeshTriangle>("../models/cornellbox/floor.obj", white, "floor");
    std::shared_ptr<MeshTriangle> shortbox = std::make_shared<MeshTriangle>("../models/cornellbox/shortbox.obj", white);
    std::shared_ptr<MeshTriangle> tallbox = std::make_shared<MeshTriangle>("../models/cornellbox/tallbox.obj", white);
    std::shared_ptr<MeshTriangle> left = std::make_shared<MeshTriangle>("../models/cornellbox/left.obj", red, "left");
    std::shared_ptr<MeshTriangle> right = std::make_shared<MeshTriangle>("../models/cornellbox/right.obj", green, "right");
    std::shared_ptr<MeshTriangle> lightMesh = std::make_shared<MeshTriangle>("../models/cornellbox/light.obj", light, "light");

    scene.addObject(floor);
    scene.addObject(shortbox);
    scene.addObject(tallbox);
    scene.addObject(left);
    scene.addObject(right);
    scene.addObject(lightMesh);
    
    scene.buildBVH();
    Renderer renderer;
    auto start = std::chrono::system_clock::now();
    renderer.render(scene);
    auto stop = std::chrono::system_clock::now();

    std::cout << "Render complete: \n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() << " minutes\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << " seconds\n";
    return 0;
}