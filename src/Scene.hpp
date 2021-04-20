#pragma once


#include <vector>
#include <memory>
#include <limits>

#include "geometry/Object.hpp"
#include "material/Material.hpp"
#include "geometry/Ray.hpp"
#include "accelerator/BVH.hpp"

class Scene {
public:
    Scene(){};
    ~Scene(){};
    void addObject(std::shared_ptr<Object> object) {
        objects.push_back(object);
    }

    void buildBVH(float time0, float time1) {
        bvh = std::make_shared<BVHAccelerator>(objects, time0, time1);
    }

    tinyMath::vec3f castRay(const Ray& ray, int depth) const {
        if(depth <=0) {
            return tinyMath::vec3f(0.0f);
        }

        std::optional<IntersectResult> r = getIntersect(ray);
        if(r.has_value()) {
            auto p = r.value();
            Ray newRay;
            tinyMath::vec3f attenuation;
            if(p.material->scatter(ray, p, attenuation, newRay)) {
                return attenuation * castRay(newRay, depth - 1);
            } else {
                return tinyMath::vec3f(0.0f);
            }
        }
       
        float t = 0.5 * (ray.d.y + 1.0f);
        return (1.0f - t) * tinyMath::vec3f(1.0) + t * tinyMath::vec3f(0.5f, 0.7f, 1.0f);
    }

private:

    std::optional<IntersectResult> getIntersect(const Ray& ray) const{
        if(bvh == nullptr) {
            return std::nullopt;
        } else {
            return bvh->intersect(ray, 0.001f, std::numeric_limits<float>::infinity());
        }
    }

    std::vector<std::shared_ptr<Object>> objects;
    std::shared_ptr<BVHAccelerator> bvh;
};