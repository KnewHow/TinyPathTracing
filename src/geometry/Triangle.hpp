#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <memory>

#include "Object.hpp"
#include "material/Material.hpp"
#include "Bounds.hpp"

class Triangle: public Object, public std::enable_shared_from_this<Triangle> {
public:
    /**
     * The three points of triangle, you should give them in clockwise
    */
    Triangle(const tinyMath::vec3f& a, const tinyMath::vec3f& b, const tinyMath::vec3f& c, std::shared_ptr<Material> m);
    ~Triangle();
    virtual std::optional<Intersection> getIntersection(const Ray& ray) const override;
    virtual Bounds getBounds() const override;
    virtual float getArea() const override;
    virtual bool isEmit() const override; 
private:
    tinyMath::vec3f v0, v1, v2;
    tinyMath::vec3f e1, e2;
    tinyMath::vec3f normal;
    float area;
    Bounds bounding;
    std::shared_ptr<Material> material;
};

#endif