#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Scene.hpp"

class Renderer {
public:
    Renderer(){};
    ~Renderer(){};
    void render(const Scene& scene);
};


#endif