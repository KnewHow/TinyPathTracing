#include "Renderer.hpp"

#include <atomic>
#include <fstream>

void Renderer::render(const Scene& scene) {
    std::vector<tinyMath::vec3f> framebuff(scene.getWidth() * scene.getHeight());
    float scale = std::tan(deg2rad(scene.getFov() * 0.5));
    float imageRatio = (float) scene.getWidth() / scene.getHeight();
    tinyMath::vec3f eye_pos = tinyMath::vec3f(278, 273, -800);
    std::atomic_int p = 0;
    int spp = 4;
    std::cout << "SPP is: " << spp << std::endl;

    #pragma omp parallel for
    for(int j = 0; j < scene.getHeight(); j++) {
        for(int i = 0; i < scene.getWidth(); i++) {
            float x = (2 * (i + 0.5) / (float)scene.getWidth() - 1) *
                      imageRatio * scale;
            float y = (1 - 2 * (j + 0.5) / (float)scene.getHeight()) * scale;

            tinyMath::vec3f dir = tinyMath::vec3f(-x, y, 1).normalize();
            Ray ray(eye_pos, dir);
            for(int k = 0; k < spp; k++) {
                int idx = j * scene.getWidth() + i;
                framebuff[idx] = framebuff[idx] + scene.castRay(ray, 0, i, j) / spp;
            }
        }
        p++;
        updateProgress((float)p / scene.getWidth());
    }

    updateProgress(1.0);

    // save to file
    FILE* fp = fopen("result.ppm", "wb");
    (void)fprintf(fp, "P6\n%d %d\n255\n", scene.getWidth(), scene.getWidth());
    for(int i = 0; i < framebuff.size(); i++) {
        static unsigned char color[3];
        color[0] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuff[i].x), 0.6f));
        color[1] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuff[i].y), 0.6f));
        color[2] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuff[i].z), 0.6f));
        fwrite(color, 1, 3, fp);
    }
    fclose(fp);
}