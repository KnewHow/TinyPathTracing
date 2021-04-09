#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <memory>

#include "Object.hpp"
#include "material/Material.hpp"

class Sphere: public Object, public std::enable_shared_from_this<Sphere>{
public:
    Sphere(const tinyMath::vec3f& c, float r, std::shared_ptr<Material> m);
    virtual std::optional<Intersection> getIntersection(const Ray& ray) const override;
    virtual Bounds getBounds() const override;
    virtual float getArea() const override;
    virtual bool isEmit() const override; 
    ~Sphere();
private:
    tinyMath::vec3f center;
    float radius;
    std::shared_ptr<Material> material;
    float area;
    Bounds bounding;
};


#endif