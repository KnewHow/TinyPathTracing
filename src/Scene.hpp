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
    Scene(){
        background = tinyMath::vec3f(0.0f);
    };
    Scene(const tinyMath::vec3f& _background): background(_background) {}
    ~Scene(){};
    
    void addObject(std::shared_ptr<Object> object) {
        objects.push_back(object);
    }

    void buildBVH(float time0, float time1) {
        bvh = std::make_shared<BVHAccelerator>(objects, time0, time1);
    }

    void setBackground(const tinyMath::vec3f& _background) {
        background = _background;
    }

    tinyMath::vec3f castRay(const Ray& ray, int depth) const {
        if(depth <=0) {
            return tinyMath::vec3f(0.0f);
        }

        std::optional<IntersectResult> r = getIntersect(ray);
        if(r.has_value()) {
            auto p = r.value();
            tinyMath::vec3f emitColor = p.material->emitted(p.u, p.v, p.coords);
            Ray newRay;
            tinyMath::vec3f attenuation;
            if(p.material->scatter(ray, p, attenuation, newRay)) {
                return emitColor + attenuation * castRay(newRay, depth - 1);
            } else {
                return emitColor;
            }
        } else {
            return background;
        }

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
    tinyMath::vec3f background;
};