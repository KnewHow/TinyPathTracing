#pragma once

#include <iostream>
#include <random>
#include <chrono>


float get_random_float() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    return dis(gen);
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