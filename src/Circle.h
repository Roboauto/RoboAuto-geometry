//
// Created by Martin Miksik on 28/05/2018.
//

#pragma once

#include "Vector.h"
#include "Polygon.h"
#include "Line.h"

#include <vector>
#include <cmath>

class Circle : public GeometryMath::DistanceTrait, public GeometryMath::ContainsTrait {
public:
    Circle(double _radius, const Vector& _center) : center(_center), radius(_radius) {};

    bool intersect(const Line& line) const {
        auto v = line.nearestVector(center);
        return contains(v);
    }

    std::vector<Vector> intersection(const Line& l) const {
        Vector nearest = l.nearestVector(center);
        double d = distance(nearest); //lec
        std::vector<Vector> solutions = {};

        if (d == radius) {
            //1 solution
            solutions.push_back(nearest);

        } else if (d < radius) {
            // 2 solutions
            double t = (center - l.from) * l.direction();
            double dt = std::sqrt(radius * radius - d * d);

            Vector inter1 = (l.direction() * (t - dt)) + l.from;
            Vector inter2 = (l.direction() * (t + dt)) + l.from;


            if (l.onSegment(inter1)) {
                solutions.push_back(inter1);
            }

            if (l.onSegment(inter2)) {
                solutions.push_back(inter2);
            }

        }

        return solutions;
    }


    Vector center;
    double radius;

};