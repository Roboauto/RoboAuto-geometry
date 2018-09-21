//
// Created by Martin Miksik on 21/05/2018.
//

#pragma once

#include <cmath>
#include <sstream>
#include "Drawable.h"
#include "Geometry.h"

#ifdef QT_DRAW
#include <QScatterSeries>
#endif


class Vector3 : public Drawable, public GeometryMath::DistanceTrait {
public:
    Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};

    Vector3() : x(0), y(0), z(0) {};

//
//    double alpha() const {
//        return std::atan2(y, x);
//    }


//    //TODO: Check
//    double angleWith(Vector3& vector) const {
//        return std::abs(alpha() - vector.alpha());
//    }


//    double crossProduct(Vector3& vector) const {
//        return x * vector.y - y * vector.x;
//    }

    double length() const {
        return std::pow(x * x + y * y + z * z, 1./3.);
    }


//    Vector3 normalVector() {
//        return {x, -y};
//    }

//    Vector3 rotate(double radian, const Vector3& center = {0, 0}) {
//        double s = std::sin(radian);
//        double c = std::cos(radian);
//
//        double nx = x - center.x;
//        double ny = y - center.y;
//
//        return {
//                (nx * c - ny * s) + center.x,
//                (nx * s + ny * c) + center.y
//        };
//    }

    double dotProduct(const Vector3 &vec) {
        return x*vec.x + y*vec.y + z*vec.z;
    }

    bool operator==(Vector3 vector) const {
        return x == vector.x && y == vector.y && z == vector.z;
    }


    bool operator!=(Vector3 vector) const {
        return x != vector.x || y != vector.y || z != vector.z;
    }


    Vector3 operator!() const {
        return {-x, -y, -z};
    }


    Vector3 operator+(Vector3 vector) const {
        return {x + vector.x, y + vector.y, z + vector.z};
    }


//    double operator+(double i) {
//        return length() + i;
//    }


    Vector3 operator-(Vector3 vector) const {
        return {x - vector.x, y - vector.y, z - vector.z};
    }


//    double operator-(double const i) const {
//        return length() - i;
//    }


    Vector3 operator*(double i) const {
        return {i * x, i * y, i * z};
    }


    double operator*(Vector3 vector) const {
        return x * vector.x + y * vector.y + z * vector.z;
    }


    //TODO: Tests
    double operator/(Vector3 vector) const {
        return x / vector.x + y / vector.y + z / vector.z;
    }


    Vector3 operator/(double i) const {
        return {x / i, y / i, z / i};
    }

    explicit operator std::string() const {
        return "[" + std::to_string(x) + "," + std::to_string(y) + "]";
    }

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    double getZ() const {
        return z;
    }
private:
    double x;
    double y;
    double z;
};