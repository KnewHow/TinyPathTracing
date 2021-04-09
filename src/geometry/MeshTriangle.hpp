#ifndef __MESHTRIANGLE_H__
#define __MESHTRIANGLE_H__

#include <string>
#include <vector>
#include <memory>

#include "Object.hpp"
#include "Triangle.hpp"
#include "Bounds.hpp"
#include "material/Material.hpp"
#include "accelerator/BVH.hpp"

class MeshTriangle: public Object, public std::enable_shared_from_this<MeshTriangle> {
public:
    MeshTriangle(const std::string& path, std::shared_ptr<Material> m);
    ~MeshTriangle();
    virtual std::optional<Intersection> getIntersection(const Ray& ray) const override;
    virtual Bounds getBounds() const override;
    virtual float getArea() const override;
    virtual bool isEmit() const override;
private:
    std::string filepath;
    std::vector<std::shared_ptr<Triangle>> triangles;
    float area;
    Bounds bounding;
    std::shared_ptr<Material> material;
    std::shared_ptr<BVH> bvh;
};

#endif