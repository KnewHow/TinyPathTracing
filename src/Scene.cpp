#include "Scene.hpp"

Scene::Scene(int w, int h)
    :width(w), height(h), objects(), bvh(nullptr){}

Scene::~Scene(){}

void Scene::addObject(std::shared_ptr<Object> object) {
    objects.push_back(object);
}

void Scene::buildBVH() {
    bvh = std::make_shared<BVH>(objects);
}

std::optional<Intersection> Scene::intersect(const Ray& ray) const {
    return bvh->intersect(ray);
}

void Scene::sampleLight(Intersection& pos, float& pdf) const {
    float emit_area_sum = 0.0f;
    for(const auto& o: objects) {
        if(o->isEmit())
            emit_area_sum += o->getArea();
    }
    float p = get_random_float() * emit_area_sum;
    emit_area_sum = 0.0;
    for(const auto& o: objects) {
        if(o->isEmit()) {
            emit_area_sum += o->getArea();
            if(emit_area_sum >= p) {
                o->sample(pos, pdf);
                return;
            }
        }
    }
}

tinyMath::vec3f Scene::castRay(const Ray& ray, int depth, int i, int j) const {
    auto cast_r = intersect(ray);
    tinyMath::vec3f l_dir = tinyMath::vec3f(0.0, 0.0, 0.0);
    tinyMath::vec3f l_indir = tinyMath::vec3f(0.0, 0.0, 0.0);
    if(cast_r.has_value()) {
        Intersection p = cast_r.value();
        Intersection light;
        float light_pdf;
        sampleLight(light, light_pdf);
        tinyMath::vec3f wo = ray.d;
        tinyMath::vec3f n = p.normal;
        tinyMath::vec3f ws = (light.coords - p.coords).normalize();
        Ray test_ray_to_light(p.coords, ws);
        auto test_r = this->intersect(test_ray_to_light);
        float distance2 = (light.coords - p.coords).norm2();
        if(test_r.has_value()) { // light no block
            float d = (test_r.value().coords - light.coords).norm();
            if(d < 0.1) {
                auto brdf = p.material->eval(ws, wo, n);
                l_dir = tinyMath::vec3f(light.emit.x * brdf.x, light.emit.y * brdf.y, light.emit.z * brdf.z) * (n * ws) * (light.normal * -ws) /  distance2 / light_pdf; 
            } 
        }

        float ksi = get_random_float();
        if(ksi < RussianRoulette) {
            tinyMath::vec3f wi = (p.material->sample(wo, n)).normalize();
            Ray wi_ray(p.coords, wi);
            auto indir_res = intersect(wi_ray);
            if(indir_res.has_value() && !(indir_res.value().object->isEmit())) {
                auto light_emit = castRay(wi_ray, depth + 1, i, j);
                auto brdf = p.material->eval(wi, wo, n);
                l_indir = tinyMath::vec3f(light_emit.x * brdf.x, light_emit.y * brdf.y, light_emit.z * brdf.z) * (n * wi) / p.material->pdf(wi, wo, n) / RussianRoulette;
            }
        }

        // if(depth < 2) { // assign light bounce times
        //     tinyMath::vec3f wi = (p.material->sample(wo, n)).normalize();
            
        //     Ray wi_ray(p.coords, wi);
        //     auto indir_res = intersect(wi_ray);
        //     if(indir_res.has_value() && !(indir_res.value().object->isEmit())) {
        //         auto light_emit = castRay(wi_ray, depth + 1, i, j);
        //         auto brdf = p.material->eval(wi, wo, n);
        //         l_indir = tinyMath::vec3f(light_emit.x * brdf.x, light_emit.y * brdf.y, light_emit.z * brdf.z) * (n * wi) / p.material->pdf(wi, wo, n);
        //     }
        // }
    }
    return l_dir + l_indir;
}
