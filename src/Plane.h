#pragma once

#include "Vector3.h"

class Plane {
public:
    Plane(const Vector3& origin_ = {0,0,0}, const Vector3& normal_ = {0,0,1}) : origin(origin_), normal(normal_) {

    }

    Vector3 getOrigin(){
        return origin;
    }

    Vector3 getNormal(){
        return normal;
    }

private:
    Vector3 origin{};
    Vector3 normal{};
};
