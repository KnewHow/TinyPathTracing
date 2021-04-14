#pragma once


#include <vector>
#include <memory>
#include <limits>

#include "geometry/Object.hpp"

class Scene {
public:
    Scene(){};
    ~Scene(){};
    void addObject(std::shared_ptr<Object> object) {
        objects.push_back(object);
    }

    tinyMath::vec3f castRay(const Ray& ray, int depth) const {
        if(depth <=0) {
            return tinyMath::vec3f(0.0f);
        }

        for(const auto& obj: objects) {
           std::optional<IntersectResult> r = obj->intersect(ray, 0.001f, std::numeric_limits<float>::infinity());
           if(r.has_value()) {
               auto p = r.value();
               return 0.5 * castRay(Ray::sampleWithHemisphere(p.coords, p.normal), depth - 1);
           }
        }

        float t = 0.5 * (ray.d.y + 1.0f);
        return (1.0f - t) * tinyMath::vec3f(1.0) + t * tinyMath::vec3f(0.5f, 0.7f, 1.0f);
    }

private:
    std::vector<std::shared_ptr<Object>> objects;
};