#include <iostream>
#include "Vector.hpp"
#include "common/Tools.hpp"
#include "material/Material.hpp"
#include "geometry/Sphere.hpp"
#include "geometry/Triangle.hpp"

int main() {
    std::shared_ptr<Material> m = std::make_shared<Material>(MaterialType::DIFFUSE, tinyMath::vec3f(1.0, 1.0, 1.0));
    tinyMath::vec3f v =  tinyMath::vec3f(0,0,0);
    // std::shared_ptr<Sphere> s = std::make_shared<Sphere>(tinyMath::vec3f(0,0,0), 1, m);
    std::shared_ptr<Triangle> t = std::make_shared<Triangle>(tinyMath::vec3f(1,0,0), tinyMath::vec3f(0,1,0), tinyMath::vec3f(0,0,1), m);
    // std::cout << "v is:" << v << std::endl;    
    return 0;
}