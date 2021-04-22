#pragma once

#include <memory>
#include <limits>

#include "Object.hpp"
#include "BoundingBox.hpp"
#include "texture/Texture.hpp"
#include "material/Isotropic.hpp"

/**
 * a constant medium to volume like smoke/fog/mist
*/
class ConstantMedium: public Object {
public:
    ConstantMedium(std::shared_ptr<Object> _boundary, float density, std::shared_ptr<Texture> texture)
        :boundary(_boundary), neg_inv_density(-1.0f / density), material(std::make_shared<Isotropic>(texture)){}
    
    ConstantMedium(std::shared_ptr<Object> _boundary, float density, const tinyMath::vec3f& color)
        :boundary(_boundary), neg_inv_density(-1.0f / density), material(std::make_shared<Isotropic>(color)){}
    ~ConstantMedium(){}

    virtual std::optional<IntersectResult> intersect(const Ray& ray, float t_min, float t_max) const { // this method goal is findding a point between two points which ray intersect with this object
        const bool enableDebug = false;
        const bool debugging = enableDebug && get_random_float() < 0.00001;
        
        // find two points the ray intersect with the object
        auto res0 = boundary->intersect(ray, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
        if(!res0.has_value()) {
            return std::nullopt;
        }
        auto p0 = res0.value();
        auto res1 = boundary->intersect(ray, p0.t + 0.0001, std::numeric_limits<float>::infinity());
        if(!res1.has_value()) {
            return std::nullopt;
        }
        auto p1 = res1.value();

        if(debugging) {
            std::cerr << "\nt_min=" << p0.t << ", t_max=" << p1.t << std::endl;
        }

        if(p0.t < t_min) p0.t = t_min;
        if(p1.t > t_max) p1.t = t_max;

        if(p0.t >= p1.t) 
            return std::nullopt;
        
        if(p0.t < 0) 
            p0.t = 0.0f;
        
        const auto ray_length = ray.d.norm();
        const auto distance_inside_boundary = (p1.t - p0.t) * ray_length;
        const auto hit_distance = neg_inv_density * std::log(get_random_float()); // get a random distance from(0, +infinity)

        if(hit_distance > distance_inside_boundary) {
            return std::nullopt;
        }

        IntersectResult r;
        r.t = p0.t + hit_distance / ray_length; // now, hit_distance is between p0 and p1, so we get t between p0 and p1
        r.coords = ray.at(r.t);
        
        if(debugging) {
            std::cerr << "hit distance=" << hit_distance << "\n"
                      << "hit t" << r.t << "\n"
                      << "hit point" << r.coords << "\n";
        }

        r.normal = tinyMath::vec3f(1.0f, 0.0f, 0.0f);
        r.isFrontFace = true;
        r.material = this->material;

        return r;
    }

    virtual BoundingBox getBoundingBox(float time0, float time1) const {
        return boundary->getBoundingBox(time0, time1);
    }


private:
    std::shared_ptr<Object> boundary;
    std::shared_ptr<Material> material;
    float neg_inv_density;
};