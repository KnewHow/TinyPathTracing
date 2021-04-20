#pragma once

/**
 * a Texture basic class
*/

#include "Vector.hpp"

class Texture {
public:
    /**
     * get color from texture, it is abstruct method, all sub class should implement it
     * @param u the u coordinates in texture
     * @param v the v coordinates in texture
     * @param point the hit point
    */
    virtual tinyMath::vec3f value(float u, float v, const tinyMath::vec3f& point) const = 0;
};