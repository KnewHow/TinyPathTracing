#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Vector.hpp"
#include "common/Tools.hpp"

/**
 * define material type, in this case, we are only use diffuse
*/
enum class MaterialType {
    DIFFUSE = 1
};

/**
 * a material class to define object type, diffuse, emitProperties and some others
*/
class Material {
public:
    Material(MaterialType t, const tinyMath::vec3f& em);
    ~Material();

    inline void setKd(const tinyMath::vec3f& v) {
        Kd = v;
    }

    inline bool isEmit() const {
        if(emission.norm() > EPSILON) 
            return true;
        else 
            return false;
    }

    inline tinyMath::vec3f getEmission() { return emission; }
     /**
     * sample in a hemisphere according output wo and normal, generating a random input ray wi
    */
    tinyMath::vec3f sample(const tinyMath::vec3f& wo, const tinyMath::vec3f& normal) const;

    /**
     * sample pdf(probability density function) from hemishpere, in this case, we simple use 1 / (2 * pi) if dot(wo, normal) > 0
     * why use  1 / (2 * pi), because hemisphere solid angle is 2 * pi.
    */
    float pdf(const tinyMath::vec3f& wi, const tinyMath::vec3f& wo, const tinyMath::vec3f& normal) const;

    /**
     * get BRDF(Bidirectional reflectance distribution function) from current object
    */
    tinyMath::vec3f eval(const tinyMath::vec3f& wi, const tinyMath::vec3f& wo, const tinyMath::vec3f& normal) const;

private:
    MaterialType type;
    tinyMath::vec3f emission; // the intensity of emission
    tinyMath::vec3f Kd;
    tinyMath::vec3f Ks;

};

#endif