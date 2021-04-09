#ifndef __TOOL_H__
#define __TOOL_H__

#include <random>
#include <chrono>

const float EPSILON = 0.0001;

inline float get_random_float() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> dist(0.0, 1.0);
    return dist(rng);
}



#endif