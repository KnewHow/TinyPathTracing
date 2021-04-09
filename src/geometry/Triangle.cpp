#include "Triangle.hpp"
#include "Ray.hpp"

Triangle::Triangle(const tinyMath::vec3f& a, const tinyMath::vec3f& b, const tinyMath::vec3f& c, std::shared_ptr<Material> m) 
    :v0(a), v1(b), v2(c), e1(b - a), e2(c - a), material(m)
{
    normal = tinyMath::cross(e1, e2).normalize();
    area = 0.5f * tinyMath::cross(e1, e2).norm();
    bounding = Bounds(v0, v1).merge(v2);
}

Triangle::~Triangle() {}

std::optional<Intersection> Triangle::getIntersection(const Ray& ray) const {
    tinyMath::vec3f S = ray.o - v0;
    tinyMath::vec3f S1 = tinyMath::cross(ray.d, e2);
    tinyMath::vec3f S2 = tinyMath::cross(S, e1);
    tinyMath::vec3f v = tinyMath::vec3f(S2 * e2, S1 * S, S2 * ray.d);
    tinyMath::vec3f r = 1 / (S1 * e1) * v;
    if(r.x > 0 && r.y > 0 && r.z > 0 && (1 - r.y - r.z) > 0) {
        float t = r.x;
        tinyMath::vec3f hitPoint = ray.o + t * ray.d;
        return Intersection{t, hitPoint, normal, shared_from_this(), material, material->getEmission()};
    } else {
        return std::nullopt;
    }
}

Bounds Triangle::getBounds() const {
    return bounding;
}

float Triangle::getArea() const {
    return area;
}

bool Triangle::isEmit() const {
    return material->isEmit();
}

void Triangle::sample(Intersection& pos, float& pdf) const { // use Barycentric coordinate sample
    float x = std::sqrt(get_random_float()), y = get_random_float();
    pos.coords = v0 * (1.0f - x) + v1 * (x * (1.0f - y)) + v2 * (x * y);
    pos.normal = this->normal;
    pdf = 1.0f / area;
}

