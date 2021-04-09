#include "Sphere.hpp"

#include "Ray.hpp"

Sphere::Sphere(const tinyMath::vec3f& c, float r, std::shared_ptr<Material> m) 
    :center(c), radius(r), material(m), area(4 * M_PI * r * r)
{
    bounding = Bounds(
        tinyMath::vec3f(center.x - r, center.y - r, center.z - r),
        tinyMath::vec3f(center.x + r, center.y + r, center.z + r)
    );
}

Sphere::~Sphere() {

}

std::optional<Intersection> Sphere::getIntersection(const Ray& ray) const {
    tinyMath::vec3f L = center - ray.o;
    float tca = L * ray.d;
    float d2 = L * L - tca * tca;
    if(d2 > radius * radius) return std::nullopt;
    float thc = sqrtf(radius * radius - d2);
    float t = tca - thc;
    float t1 = tca + thc;
    if(t < 0) t = t1;
    if(t < 0)  return std::nullopt;
    tinyMath::vec3f hitPoint = ray.o + t * ray.d;
    tinyMath::vec3f normal = (hitPoint - center).normalize();
    return Intersection{t, hitPoint, normal, shared_from_this(), material};
}   

Bounds Sphere::getBounds() const {
    return bounding;
}

float Sphere::getArea() const {
    return area;
}

bool Sphere::isEmit() const {
    return material->isEmit();
}