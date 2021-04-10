#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <memory>

#include "geometry/Object.hpp"
#include "geometry/Ray.hpp"
#include "accelerator/BVH.hpp"

class Scene {
public:
    Scene(int w, int h);
    ~Scene();
    void addObject(std::shared_ptr<Object> object);
    /**
     * when you add all mesh into scene, you should call this function to build a BVH to accelerate ray intersecting with secne objects
    */
    void buildBVH();

    /**
     * Casting ray intersect with the scene, it they are intersecting, return the intersect result, otherwise return nullopt
     * in this case, we use bvh to accelerate intersection.
     * @param ray the ray
     * @return it they are intersecting, return the intersect result, otherwise return nullopt
    */
    std::optional<Intersection> intersect(const Ray& ray) const;
    
    /**
     * cast ray intersectes with scene
     * @param ray the ray
     * @param depth the depth of ray bounce
     * @return the radiace of the ray
    */
    tinyMath::vec3f castRay(const Ray& ray, int depth = 0) const;

    inline float getFov() const { return fov; }
    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
   
private:
    int width, height;
    std::vector<std::shared_ptr<Object>> objects;
    std::shared_ptr<BVH> bvh;
    float RussianRoulette = 0.8;
    float fov = 40.0f;
    
    /**
     * Sample from light source
     * @param pos the position of ligth source
     * @param pdf the probability density function of light source
    */
    void sampleLight(Intersection& pos, float& pdf) const;
};

#endif