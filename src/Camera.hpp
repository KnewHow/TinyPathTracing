#pragma once

#include "Vector.hpp"

struct Camera {
public:
    /**
     * the construct of camera
     * @param lookfrom the point camera look from
     * @param lookat the point camera look at
     * @param vup the view up vector
     * @param fov the field of view, the unit is degree
     * @param aspect_ratio the ratio of scren, calculating with: width / height
    */
    Camera(tinyMath::vec3f lookfrom, 
        tinyMath::vec3f lookat, 
        tinyMath::vec3f vup, 
        float fov, 
        float aspect_ratio, float aperture, float focus_dist)
    {

        w = (lookfrom - lookat).normalize();
        u = tinyMath::cross(vup, w).normalize();
        v = tinyMath::cross(w, u).normalize();
        float h = std::tan(degree2Radian(fov) / 2.0f);
        float viewport_height = 2.0f * h;
        float viewport_width = viewport_height * aspect_ratio;
        
        origin = lookfrom;
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - (horizontal / 2.0) - (vertical / 2.0) - focus_dist * w; // let standard square equal ratio with image
        lens_radius = aperture / 2.0f;
    }

    Ray getRay(float s, float t) const {
        tinyMath::vec3f rd = lens_radius * get_random_in_unit_disk();
        tinyMath::vec3f offset = u * rd.x + v * rd.y;
        tinyMath::vec3f d = (lower_left_corner + s * horizontal + t * vertical - origin - offset).normalize();
        Ray ray(origin + offset, d);
        return ray;
    }

    ~Camera(){}
private:
    tinyMath::vec3f u, v, w;
    tinyMath::vec3f origin;
    tinyMath::vec3f horizontal;
    tinyMath::vec3f vertical;
    tinyMath::vec3f lower_left_corner;
    float lens_radius;

public:
    const int samples_per_pixel = 500;

};