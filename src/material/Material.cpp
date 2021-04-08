#include "Material.hpp"

Material::Material(MaterialType t, tinyMath::vec3f em)
    :type(t), emission(em)
{

}

Material::~Material() {

}

tinyMath::vec3f Material::sample(const tinyMath::vec3f& wo, const tinyMath::vec3f& normal) const {
    
}

