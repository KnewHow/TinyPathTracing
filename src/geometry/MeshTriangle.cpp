#include "MeshTriangle.hpp"

#include <array>

#include "OBJ_Loader.hpp"
#include "Ray.hpp"

MeshTriangle::MeshTriangle(const std::string& path, std::shared_ptr<Material> m, const std::string& _name)
    :filepath(path), material(m), area(0.0f), triangles(),bounding(), bvh(nullptr), name(_name)
{
   objl::Loader loader = objl::Loader();
   if(!loader.LoadFile(path)) {
       std::cerr << "mesh path error: " << filepath << std::endl;
       return;
   }
   assert(loader.LoadedMeshes.size() == 1);
   auto mesh = loader.LoadedMeshes[0];
   std::vector<std::shared_ptr<Object>> objs;
   for(int i = 0; i < mesh.Vertices.size(); i += 3) {
       std::array<tinyMath::vec3f, 3> arr;
       for(int j = 0; j < 3; j++) {
           arr[j] = tinyMath::vec3f(
               mesh.Vertices[i + j].Position.X,
               mesh.Vertices[i + j].Position.Y,
               mesh.Vertices[i + j].Position.Z
           );
       }
       std::shared_ptr<Triangle> t = std::make_shared<Triangle>(arr[0], arr[1],arr[2], m, this->name);
       area += t->getArea();
       bounding = bounding.merge(t->getBounds());
       triangles.push_back(t);
       objs.push_back(t);
   }

   bvh = std::make_shared<BVH>(objs);
}

MeshTriangle::~MeshTriangle(){}

std::optional<Intersection> MeshTriangle::getIntersection(const Ray& ray) const {
    return bvh->intersect(ray);
}

Bounds MeshTriangle::getBounds() const {
    return bounding;
}

float MeshTriangle::getArea() const {
    return area;
}

bool MeshTriangle::isEmit() const {
    return material->isEmit();
}

void MeshTriangle::sample(Intersection& pos, float& pdf) const {
    bvh->sample(pos, pdf);
    pos.emit = material->getEmission();
}