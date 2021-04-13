#pragma once

class Scene {
public:
    Scene(){};
    ~Scene(){};
    tinyMath::vec3f castRay(const Ray& ray) const {
        float t = 0.5 * (ray.d.y + 1.0f);
        return (1.0f - t) * tinyMath::vec3f(1.0) + t * tinyMath::vec3f(0.5f, 0.7f, 1.0f);
    }
};