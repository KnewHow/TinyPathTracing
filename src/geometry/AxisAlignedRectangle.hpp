#pragma once

#include <memory>

#include "Object.hpp"
#include "BoundingBox.hpp"
#include "material/Material.hpp"

/**
 * a rectangle in X-Y plane
*/

const float DELTA_RECTANGLE_THICKNESS = 0.0001; // let rectangle has some thickness, it will make ray intersect with it

class XYRectangle: public Object {
public:
    XYRectangle(float _x0, float _x1, float _y0, float _y1, float _z, std::shared_ptr<Material> _material)
        :x0(_x0), x1(_x1), y0(_y0), y1(_y1), z(_z), material(_material){}
    ~XYRectangle(){}

    virtual std::optional<IntersectResult> intersect(const Ray& ray, float t_min, float t_max) const override {
        float t = (z - ray.o.z) / ray.d.z;
        if(t < t_min || t > t_max) {
            return std::nullopt;
        }

        float x = ray.o.x + t * ray.d.x;
        float y = ray.o.y + t * ray.d.y;

        if(x < x0 || x > x1 || y < y0 || y > y1) {
            return std::nullopt;
        }

        float u = (x - x0) / (x1 - x0);
        float v = (y - y0) / (y1 - y0);
        tinyMath::vec3f outward_normal =  tinyMath::vec3f(0, 0, 1);

        IntersectResult r;
        r.t = t;
        r.u = u;
        r.v = v;
        r.coords = ray.at(t);
        r.setFrontFace(ray, outward_normal);
        r.material = this->material;
        return r;
    }

    virtual BoundingBox getBoundingBox(float time0, float time1) const override {
        BoundingBox bbox(tinyMath::vec3f(x0, y0, z - DELTA_RECTANGLE_THICKNESS), tinyMath::vec3f(x1, y1, z + DELTA_RECTANGLE_THICKNESS));
        return bbox;
    }

    float x0, x1, y0, y1, z;
    std::shared_ptr<Material> material;
};

/**
 * a rectangle in X-Z plane
*/
class XZRectangle: public Object {
public:
    XZRectangle(float _x0, float _x1, float _z0, float _z1, float _y, std::shared_ptr<Material> _material)
        :x0(_x0), x1(_x1), z0(_z0), z1(_z1), y(_y), material(_material){}
    ~XZRectangle(){}
   
    virtual std::optional<IntersectResult> intersect(const Ray& ray, float t_min, float t_max) const override {
        float t = (y - ray.o.y) / ray.d.y;
        if(t < t_min || t > t_max) {
            return std::nullopt;
        }

        float x = ray.o.x + t * ray.d.x;
        float z = ray.o.z + t * ray.d.z;

        if(x < x0 || x > x1 || z < z0 || z > z1) {
            return std::nullopt;
        }

        float u = (x - x0) / (x1 - x0);
        float v = (z - z0) / (z1 - x0);

        tinyMath::vec3f outward_normal =  tinyMath::vec3f(0, 1, 0);

        IntersectResult r;
        r.t = t;
        r.u = u;
        r.v = v;
        r.coords = ray.at(t);
        r.setFrontFace(ray, outward_normal);
        r.material = this->material;
        return r;
    }

    virtual BoundingBox getBoundingBox(float time0, float time1) const override {
        BoundingBox bbox(tinyMath::vec3f(x0, y - DELTA_RECTANGLE_THICKNESS, z0), tinyMath::vec3f(x1, y + DELTA_RECTANGLE_THICKNESS, z1));
        return bbox;
    }


    float x0, x1, z0, z1, y;
    std::shared_ptr<Material> material;
};

class YZRectangle: public Object {
public:
    YZRectangle(float _y0, float _y1, float _z0, float _z1, float _x, std::shared_ptr<Material> _material)
        :y0(_y0), y1(_y1), z0(_z0), z1(_z1), x(_x), material(_material){}
    ~YZRectangle(){}
    
    virtual std::optional<IntersectResult> intersect(const Ray& ray, float t_min, float t_max) const override {
        float t = (x - ray.o.x) / ray.d.x;
        if(t < t_min || t > t_max) {
            return std::nullopt;
        }

        float y = ray.o.y + t * ray.d.y;
        float z = ray.o.z + t * ray.d.z;

        if(y < y0 || y > y1 || z < z0 || z > z1) {
            return std::nullopt;
        }

        float u = (y - y0) / (y1 - y0);
        float v = (z - z0) / (z1 - z0);


        tinyMath::vec3f outward_normal =  tinyMath::vec3f(1, 0, 0);

        IntersectResult r;
        r.t = t;
        r.u = u;
        r.v = v;
        r.coords = ray.at(t);
        r.setFrontFace(ray, outward_normal);
        r.material = this->material;
        return r;
    }
    
    virtual BoundingBox getBoundingBox(float time0, float time1) const override {
        BoundingBox bbox(tinyMath::vec3f(x - DELTA_RECTANGLE_THICKNESS, y0, z0), tinyMath::vec3f(x + DELTA_RECTANGLE_THICKNESS, y1, z1));
        return bbox;
    }
    float y0, y1, z0, z1, x;
    std::shared_ptr<Material> material;
};