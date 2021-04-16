#pragma once

#include <iostream>
#include <random>
#include <chrono>

#include "Vector.hpp"

inline float clamp(float v, float min, float max){
    if(v < min)
        return min;
    else if(v > max)
        return max;
    else
        return v;
}

inline float get_random_float(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

inline float get_random_float() {
    return get_random_float(0.0f, 1.0f);
}

inline tinyMath::vec3f get_random_vector(float min, float max) {
    return tinyMath::vec3f(
        get_random_float(min, max),
        get_random_float(min, max),
        get_random_float(min, max)
    );
}

inline tinyMath::vec3f get_random_vector() {
    return tinyMath::vec3f(
        get_random_float(),
        get_random_float(),
        get_random_float()
    );
}

inline tinyMath::vec3f get_random_in_unit_disk() {
    while(true) {
        tinyMath::vec3f r = tinyMath::vec3f(get_random_float(-1.0f, 1.0f), get_random_float(-1.0f, 1.0f), 0.0f);
        if(r.norm2() >= 1)
            continue;
        return r;
    }
}


inline bool isNearZero(const tinyMath::vec3f& v) {
    float epsilon = 1e-8;
    return (std::fabs(v.x) < epsilon) && (std::fabs(v.y) < epsilon) && (std::fabs(v.z) < epsilon);
}

inline tinyMath::vec3f reflect(const tinyMath::vec3f& I, const tinyMath::vec3f& N) {
    return I - 2 * tinyMath::dotProduct(I, N) * N;
}

inline tinyMath::vec3f refract(const tinyMath::vec3f& I, const tinyMath::vec3f& N, float refraction_ratio) {
    float cos_theta = std::fmin(tinyMath::dotProduct(-I, N), 1.0f);
    tinyMath::vec3f r_perp = refraction_ratio * (I + cos_theta * N);
    tinyMath::vec3f r_parallel = -std::sqrt(std::fabs(1 - r_perp.norm2())) * N;
    return r_perp + r_parallel;
}

inline float degree2Radian(float degree) {
    return degree * M_PI / 180.0f;
}

inline tinyMath::vec3f get_random_vector_in_unit_sphere() {
    while (true)
    {
        tinyMath::vec3f v = get_random_vector(-1.0f, 1.0f);
        if(v.norm2() >= 1.0f) continue;
        return v;
    }
}



void printTimeTook(std::chrono::_V2::system_clock::time_point begin,std::chrono::_V2::system_clock::time_point end, const std::string& functionName) {
    std::cout << "run [" << functionName << "] took: \n";
    auto hours = std::chrono::duration_cast<std::chrono::hours>(end - begin).count();
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(end - begin).count() - hours * 60;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() - minutes * 60 - hours * 3600;
    std::cout << hours << " hours\n";
    std::cout << minutes << " minutes\n";
    std::cout <<  seconds << " seconds\n";
    

}

void updateProgress(float p)
{
    int width = 80;
    int complete = p * width;
    std::cout << "[";
    for(int i = 0; i < width; i++) {
        if(i < complete)
            std::cout << "=";
        else if(i == complete)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << "]" << (int)(p * 100) << "%\r";
    std::cout.flush();
}