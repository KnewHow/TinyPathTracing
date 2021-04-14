#pragma once

#include "Vector.hpp"

struct Camera {
public:
    
    Camera(float aspect_ratio)
    {
        origin = tinyMath::vec3f(0.0f, 0.0f, 0.0f);
        viewport_width = viewport_height * aspect_ratio;
        horizontal = tinyMath::vec3f(viewport_width, 0.0f, 0.0f);
        vertical = tinyMath::vec3f(0.0f, viewport_height, 0.0f);
        lower_left_corner = origin - (horizontal / 2.0) - (vertical / 2.0) - tinyMath::vec3f(0.0, 0.0, focal_length); // let standard square equal ratio with image
    }

    Ray getRay(float u, float v) const {
        tinyMath::vec3f d = (lower_left_corner + u * horizontal + v * vertical - origin).normalize();
        Ray ray(origin, d);
        return ray;
    }

    ~Camera(){}
    const float viewport_height = 2.0;
    float viewport_width = viewport_height * (16.0 / 9.0);
    const float focal_length = 1.0f;
    tinyMath::vec3f origin;
    tinyMath::vec3f horizontal;
    tinyMath::vec3f vertical;
    tinyMath::vec3f lower_left_corner;
    const int samples_per_pixel = 8;

};