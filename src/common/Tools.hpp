#ifndef __TOOL_H__
#define __TOOL_H__

#include <random>
#include <chrono>
#include <iostream>

const float EPSILON = 0.00001;

inline float get_random_float() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> dist(0.0, 1.0);
    return dist(rng);
}

inline float clamp(const float& lo, const float& hi, const float& v) {
    return std::min(hi, std::max(lo, v));
}

inline void updateProgress(float progress) {
    int barWidth = 70;
    int p = barWidth * progress;
    std::cout << "[";
    for(int i = 0; i < barWidth; i++) {
        if(i < p)
            std::cout << "=";
        else if(i == p)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << "] " << (int)(progress * 100) << "%\r";
    std::cout.flush();
}

inline float deg2rad(float degree) {
    return degree * M_PI / 180.0f;
}


#endif