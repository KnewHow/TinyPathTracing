#pragma once

#include "common/Tools.hpp"

/**
 * A perlin noise implement, code refer[5 Perlin noise]: https://raytracing.github.io/books/RayTracingTheNextWeek.html
 * you can read more from:
*/
class PerlinNoise {
public:
    
    PerlinNoise(){
        ranfloat = new float[point_counter];
        for(int i = 0; i < point_counter; i++) {
            ranfloat[i] = get_random_float();
        }
        perm_x = perlin_generate_perm();
        perm_y = perlin_generate_perm();
        perm_z = perlin_generate_perm();
    }
    
    ~PerlinNoise(){
        delete[] ranfloat;
        delete[] perm_x;
        delete[] perm_y;
        delete[] perm_z;
    }

    float noise(const tinyMath::vec3f& p) {
        float u = p.x - std::floor(p.x);
        float v = p.y - std::floor(p.y);
        float w = p.z - std::floor(p.z);
        
        int i = static_cast<int>(std::floor(p.x));
        int j = static_cast<int>(std::floor(p.y));
        int k = static_cast<int>(std::floor(p.z));

        float c[2][2][2];
        for(int di = 0; di < 2; di++) {
            for(int dj = 0; dj < 2; dj++) {
                for(int dk = 0; dk < 2; dk++) {
                    int idx = perm_x[(i + di) & 255] ^
                              perm_y[(j + dj) & 255] ^
                              perm_z[(k + dk) & 255];
                    c[di][dj][dk] = ranfloat[idx];
                }
            }
        }
        return triliner_interp(c, u, v, w);
    }

private:

    int* perlin_generate_perm() {
        int* r = new int[point_counter];
        for(int i = 0; i < point_counter; i++)
            *(r + i) = i;
        permute(r, point_counter);
        return r;
    }

    void permute(int *p, int n) {
        for(int i = n - 1; i > 0; i--) {
            int target = get_random_int(0, i);
            int temp = *(p + i);
            *(p + i)  = * (p + target);
            *(p + target) = temp;
        }
    }

    float triliner_interp(float c[2][2][2], float u, float v, float w) {
        float sum = 0.0f;
        u = hermitianSmoothing(u);
        v = hermitianSmoothing(v);
        w = hermitianSmoothing(w);
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                for(int k = 0; k < 2; k++) {
                    sum += (i * u + (1 - i) * (1 - u)) *
                           (j * v + (1 - j) * (1 - v)) *
                           (k * w + (1 - k) * (1 - w)) * c[i][j][k];
                }
            }
        }
        return sum;
    }

    inline float hermitianSmoothing(float factor) {
        return factor * factor * (3.0f - 2.0f * factor);
    }

    const int point_counter = 256;
    float* ranfloat;
    int* perm_x;
    int* perm_y;
    int* perm_z;
};