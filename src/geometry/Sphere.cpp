#include "Sphere.hpp"

#include "Ray.hpp"
#include "material/Material.hpp"

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
    return Intersection{t, hitPoint, normal, shared_from_this(), material, material->getEmission() };
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

void Sphere::sample(Intersection& pos, float& pdf) const { // shpere coordinates to Cartesian coordinates, refer(Coordinate system conversions): https://en.wikipedia.org/wiki/Spherical_coordinate_system  
    float theta = M_PI * get_random_float(), phi = 2 * M_PI * get_random_float();
    tinyMath::vec3f dir(std::cos(phi) * std::sin(theta), std::sin(phi) * std::sin(theta), std::cos(theta));
    pos.coords = center + radius * dir;
    pos.normal = dir.normalize();
    pos.emit = material->getEmission();
    pdf = 1.0f / area;
}