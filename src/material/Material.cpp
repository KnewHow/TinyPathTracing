#include "Material.hpp"

Material::Material(MaterialType t, tinyMath::vec3f em)
    :type(t), emission(em)
{

}

Material::~Material() {

}

tinyMath::vec3f toWorld(const tinyMath::vec3f& localRay, const tinyMath::vec3f& normal) {
    tinyMath::vec3f B, C;
    if(std::fabs(normal.x) > std::fabs(normal.y)) {
        float invLen = 1.0f / std::sqrt(normal.x * normal.x + normal.z + normal.z);
        C = tinyMath::vec3f(normal.z * invLen, 0.0f, -normal.x * invLen);
    } else {
        float invLen = 1.0f / std::sqrt(normal.y + normal.y + normal.z * normal.z);
        C = tinyMath::vec3f(0.0f, normal.z * invLen, -normal.y * invLen);
    }

    B = tinyMath::cross(C, normal);
    return localRay.x * B + localRay.y * C + localRay.z * normal;
}

tinyMath::vec3f Material::sample(const tinyMath::vec3f& wo, const tinyMath::vec3f& normal) const {
    switch (type)
    {
    case MaterialType::DIFFUSE:
        float x_1 = get_random_float(), x_2 = get_random_float();
        float z = std::fabs(1.0f - 2.0f * x_1);
        float r = std::sqrt(1.0f - z * z), phi = 2 * M_PI * x_2;
        tinyMath::vec3f localRay(r * std::cos(phi), r * std::sin(phi), z);
        return toWorld(localRay, normal);
        break;
    
    }
    return tinyMath::vec3f(0.0f, 0.0f, 0.0f);
}

float Material::pdf(const tinyMath::vec3f& wi, const tinyMath::vec3f& wo, const tinyMath::vec3f& normal) const {
    switch (type)
    {
    case MaterialType::DIFFUSE:
        if(wi * normal > 0.0f) {
            return 0.5f / M_PI;
        } else {
            return 0.0f;
        }
        break;
    }
    return 0.0;
}

tinyMath::vec3f Material::eval(const tinyMath::vec3f& wi, const tinyMath::vec3f& wo, const tinyMath::vec3f& normal) const {
    switch (type)
    {
    case MaterialType::DIFFUSE:
        if(wi * normal > 0.0f) {
            return Kd / M_PI;
        } else {
            return tinyMath::vec3f(0.0f, 0.0f, 0.0f);
        }
        break;
    }
    return tinyMath::vec3f(0.0f, 0.0f, 0.0f);
}

