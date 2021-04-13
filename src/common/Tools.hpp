#pragma once

#include <iostream>

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