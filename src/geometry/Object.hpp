#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <optional>


class Bounds;
class Ray;
class Intersection;

class Object {
public:
    Object(){}
    ~Object(){}    
    /**
     * get intersection result if the ray intersect with the object, otherwise return nullopt.
     * @param ray the ray 
    */
    virtual std::optional<Intersection> getIntersection(const Ray& ray) const = 0;
    
    /**
     * get the object bounding box, in this case, we use AABB box
    */
    virtual Bounds getBounds() const = 0;
    
    /**
     * get the object area, it's very useful when we do some sample
    */
    virtual float getArea() const = 0; 

    /**
     * Whether the object is emit, in subclass, you can use material property to implement it.
    */
    virtual bool isEmit() const = 0;
};

#endif