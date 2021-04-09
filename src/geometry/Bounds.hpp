#ifndef __BOUNDS_H__
#define __BOUNDS_H__

#include <limits>

#include "Vector.hpp"
#include "Ray.hpp"

/**
 * this is bounding box, in this case, we just use AABB
*/
struct Bounds {
    enum class AXIS {
        X = 1,
        Y = 2,
        Z = 3,
    };
    
    Bounds(const tinyMath::vec3f& a, const tinyMath::vec3f& b) {
        for(int i = 0; i < 3; i++) {
            min[i] = std::min(a[i], b[i]);
            max[i] = std::max(a[i], b[i]);
        }
    }
    
    Bounds() {
        min = tinyMath::vec3f(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
        max = tinyMath::vec3f(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
    }
    ~Bounds(){};

    Bounds merge(const Bounds& other) {
        Bounds res;
        for(int i = 0; i < 3; i++) {
            res.min[i] = std::min(min[i], other.min[i]);
            res.max[i] = std::max(max[i], other.max[i]);
        }
        return res;
    }

    Bounds merge(const tinyMath::vec3f& v) {
        Bounds res;
        for(int i = 0; i < 3; i++) {
            res.min[i] = std::min(min[i], v[i]);
            res.max[i] = std::max(max[i], v[i]);
        }
        return res;
    }

    tinyMath::vec3f getCentre() const {
        return (min + max) / 2.0f;
    }

    /**
     * get who axis extend is larger.
    */
    AXIS getExtent() const {
        tinyMath::vec3f d = max - min;
        if(d.x > d.y && d.x > d.z) {
            return AXIS::X;
        } else if(d.y > d.z) {
            return AXIS::Y;
        } else {
            return AXIS::Z;
        }
    }

    bool intersect(const Ray& ray) const {
        float t_min_x = (min.x - ray.o.x) / ray.d.x;
        float t_min_y = (min.y - ray.o.y) / ray.d.y;
        float t_min_z = (min.z - ray.o.z) / ray.d.z;

        float t_max_x = (max.x - ray.o.x) / ray.d.x;
        float t_max_y = (max.y - ray.o.y) / ray.d.y;
        float t_max_z = (max.z - ray.o.z) / ray.d.z;

        if(ray.d.x < 0) {
            std::swap(t_max_x, t_min_x);
        }
        if(ray.d.y < 0) {
            std::swap(t_max_y, t_min_y);
        }
        if(ray.d.z < 0) {
            std::swap(t_max_z, t_min_z);
        }

        float t_enter = std::max(t_min_x, std::max(t_min_y, t_min_z));
        float t_exit = std::min(t_max_x, std::min(t_max_y, t_max_z));
        return t_exit > t_enter && t_exit >= 0;
    }

    tinyMath::vec3f min;
    tinyMath::vec3f max;
};

#endif