#include "BVH.hpp"

#include <algorithm>
#include <chrono>

#include "common/Tools.hpp"

BVH::BVH(const std::vector<std::shared_ptr<Object>>& objs)
    :objects(objs), root(nullptr)
{
    auto begin = std::chrono::system_clock::now();
    root = recursiveBuild(objects);
    auto end = std::chrono::system_clock::now();
    std::cout << "Build BVH Time taken: " << std::chrono::duration_cast<std::chrono::hours>(end - begin).count() << " hours\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(end - begin).count() << " minutes\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << " seconds\n";

}

BVH::~BVH(){}

std::shared_ptr<BVHNode> BVH::recursiveBuild(std::vector<std::shared_ptr<Object>> objs) const {

    Bounds bouding;
    for(const auto& o: objs) {
        bouding = bouding.merge(o->getBounds());
    }

    std::shared_ptr<BVHNode> node = std::make_shared<BVHNode>();
    if(objs.size() == 1) {
        node->left = node->right = nullptr;
        node->bounding = bouding;
        node->object = objs[0];
        node->area = objs[0]->getArea();
    } else if(objs.size() == 2) {
        node->left = recursiveBuild(std::vector<std::shared_ptr<Object>>{objs[0]});
        node->right = recursiveBuild(std::vector<std::shared_ptr<Object>>{objs[1]});
        node->bounding = node->left->bounding.merge(node->right->bounding);
        node->area = node->left->area + node->right->area;
    } else {
        Bounds boudingCenter;
        for(const auto& o: objs) {
            boudingCenter = boudingCenter.merge(o->getBounds().getCentre());
        }
        Bounds::AXIS dim = boudingCenter.getExtent();
        switch (dim)
        {
        case Bounds::AXIS::X:
            std::sort(objs.begin(), objs.end(), [](std::shared_ptr<Object> o1, std::shared_ptr<Object> o2){
                return o1->getBounds().getCentre().x < o2->getBounds().getCentre().x;
            });
            break;
        case Bounds::AXIS::Y:
            std::sort(objs.begin(), objs.end(), [](std::shared_ptr<Object> o1, std::shared_ptr<Object> o2){
                return o1->getBounds().getCentre().y < o2->getBounds().getCentre().y;
            });
            break;
        
        case Bounds::AXIS::Z:
            std::sort(objs.begin(), objs.end(), [](std::shared_ptr<Object> o1, std::shared_ptr<Object> o2){
                return o1->getBounds().getCentre().z < o2->getBounds().getCentre().z;
            });
            break;
        }

        auto begin = objs.begin();
        auto middle = objs.begin() + (objs.size() / 2);
        auto end = objs.end();
        auto subLeft = std::vector<std::shared_ptr<Object>>(begin, middle);
        auto subRight = std::vector<std::shared_ptr<Object>>(middle, end);
        assert(objs.size() == (subLeft.size() + subRight.size()));
        node->left = recursiveBuild(subLeft);
        node->right = recursiveBuild(subRight);
        node->bounding = node->left->bounding.merge(node->right->bounding);
        node->area = node->left->area + node->right->area;
    }

    return node;
}


std::optional<Intersection> BVH::intersect(const Ray& ray) const {
    if(root == nullptr) 
        return std::nullopt;
    else
        return recursiveIntersect(ray, root);
}

std::optional<Intersection> BVH::recursiveIntersect(const Ray& ray, std::shared_ptr<BVHNode> r) const {
    if(r == nullptr) {
        return std::nullopt;
    } else if(r->bounding.intersect(ray)) {
        if(r->left == nullptr && r->right == nullptr) {
            return r->object->getIntersection(ray);
        } else {
            auto leftR = recursiveIntersect(ray, r->left);
            auto rightR = recursiveIntersect(ray, r->right); 
            if(leftR.has_value() && rightR.has_value()) {
                return leftR.value().t < rightR.value().t ? leftR : rightR;
            } else if(leftR.has_value()) {
                return leftR;
            } else if(rightR.has_value()) {
                return rightR;
            }
        }
    }
    return std::nullopt;
}

void BVH::sample(Intersection& pos, float& pdf) const {
    float p = std::sqrt(get_random_float()) * root->area;
    recursiveSample(root, p, pos, pdf);
    pdf /= root->area;
}

void BVH::recursiveSample(std::shared_ptr<BVHNode> r, float p, Intersection& pos, float& pdf) const {
    if(r->left == nullptr || r->right == nullptr) {
        r->object->sample(pos, pdf);
        pdf *= r->area;
        return;
    } else {
        if(r->left->area > p)
            recursiveSample(r->left, p, pos, pdf);
        else
            recursiveSample(r->right, p - r->left->area, pos, pdf);
    }
}