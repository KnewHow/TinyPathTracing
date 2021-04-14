#pragma once

#include <iostream>
#include <random>
#include <chrono>

#include "Vector.hpp"



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
    std::cout << std::chrono::duration_cast<std::chrono::hours>(end - begin).count() << " hours\n";
    std::cout << std::chrono::duration_cast<std::chrono::minutes>(end - begin).count() << " minutes\n";
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << " seconds\n";
    

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