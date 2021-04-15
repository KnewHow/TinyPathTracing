#pragma once

#include "Material.hpp"
#include "geometry/Ray.hpp"

class Dielectric: public Material{
public:
    Dielectric(float index_of_refraction)
        :ir(index_of_refraction){}
    

     virtual bool scatter(
        const Ray& ray, 
        const IntersectResult& intersect,
        tinyMath::vec3f& attenuation,
        Ray& scattered
    ) const override {
        attenuation = tinyMath::vec3f(1.0f);
        float refraction_ratio = intersect.isFrontFace ? (1.0 / ir) : ir;
        float cos_theta = std::fmin(tinyMath::dotProduct(-ray.d.normalize(), intersect.coords), 1.0f);
        float sin_theta = std::sqrt(1 - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0f;
        tinyMath::vec3f newDir = tinyMath::vec3f(0.0f);
        if(cannot_refract || reflection(cos_theta, refraction_ratio) > get_random_float()) {
            newDir = reflect(ray.d, intersect.normal);
        } else {
            newDir = refract(ray.d, intersect.normal, refraction_ratio);
        }

        scattered = Ray(intersect.coords, newDir.normalize());

        return true;
    }
    
    
    float ir;

private:
    static float reflection(float consin, float ref_idx) { // Schlick's approximation: https://en.wikipedia.org/wiki/Schlick%27s_approximation
        float R0 = (1 - ref_idx) / (1 + ref_idx);
        R0 = R0 * R0;
        float r = R0 + (1 - R0) * std::pow((1 - R0), 5);
        return r;
    }
};