#pragma once

#include <memory>

#include "../Object.hpp"
#include "../BoundingBox.hpp"
#include "common/Tools.hpp"

/**
 * a object rotate by Y-AXIS 
*/
class RotationY: public Object {
public:
    /**
     * construct a rotation object from original object
     * @param _object the original object need to rotate
     * @param degree_angle the angle to rotate, it use degree
    */
    RotationY(std::shared_ptr<Object> _object, float degree_angle)
        :object(_object) {
        float theta = degree2Radian(degree_angle);
        sin_theta = std::sin(theta);
        cos_theta = std::cos(theta);
        BoundingBox oldBox = object->getBoundingBox(0, 1);
        BoundingBox newBox;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                for(int k = 0; j < 2; k++) {
                    float x = i * oldBox.max.x + (1 - i) * oldBox.min.x;
                    float y = j * oldBox.max.y + (1 - j) * oldBox.min.y;
                    float z = k * oldBox.max.z + (1 - k) * oldBox.min.z;

                    float newX = get_x_prime(x, z);
                    float newZ = get_z_prime(x, z);

                    tinyMath::vec3f newPoint = tinyMath::vec3f(newX, y, newZ);
                    newBox = newBox.combine(newPoint);
                }
            }
        }
        bbox = newBox;
    }
    ~RotationY(){}
    virtual std::optional<IntersectResult> intersect(const Ray& ray, float t_min, float t_max) const override {
        tinyMath::vec3f origin = ray.o;
        tinyMath::vec3f direction = ray.d;
        origin.x = cos_theta * ray.o.x -sin_theta * ray.o.z;


        return std::nullopt;
    }

    virtual BoundingBox getBoundingBox(float time0, float time1) const override {
        return bbox;
    }

private:

    inline float get_x_prime(float x, float z) const {
        return cos_theta * x + sin_theta * z;
    }

    inline float get_x_prime_inverse(float x, float z) const {
        return cos_theta * x + sin_theta * z;// TODO
    }

    inline float get_z_prime(float x, float z) const {
        return -sin_theta * x + cos_theta * z;
    }

    inline float get_z_prime_inverse(float x, float z) const {
        return -sin_theta * x + cos_theta * z; // TODO
    }

    std::shared_ptr<Object> object;
    float sin_theta;
    float cos_theta;
    BoundingBox bbox;
};