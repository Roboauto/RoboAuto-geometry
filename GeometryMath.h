//
// Created by Martin Miksik on 29/05/2018.
//

#pragma once

#include <cmath>

#include "src/Vector.h"
#include "src/Vector3.h"
#include "src/Line.h"
#include "src/Polygon.h"
#include "src/Circle.h"
#include "src/Polyline.h"
#include "src/Plane.h"

namespace GeometryMath {
    template<>
    inline double distance(const Vector& v1, const Vector& v2) {
        return std::sqrt(std::pow(v1.getX() - v2.getX(), 2) + std::pow(v1.getY() - v2.getY(), 2));
    }

    template<>
    inline double distance(const Vector& v, const Line& l) {
        auto x = v.getX(), y = v.getY(), x1 = l.from.getX(), x2 = l.to.getX(), y1 = l.from.getY(), y2 = l.to.getY();
        auto A = x - x1;
        auto B = y - y1;
        auto C = x2 - x1;
        auto D = y2 - y1;

        auto dot = A * C + B * D;
        auto len_sq = C * C + D * D;
        auto param = -1.;
        if (len_sq != 0) {
            param = dot / len_sq;
        }

        double xx, yy;

        if (param < 0) {
            xx = x1;
            yy = y1;
        }
        else if (param > 1) {
            xx = x2;
            yy = y2;
        }
        else {
            xx = x1 + param * C;
            yy = y1 + param * D;
        }

        auto dx = x - xx;
        auto dy = y - yy;
        return std::sqrt(dx * dx + dy * dy);


        double d = std::sqrt(l.a * l.a + l.b * l.b);
        double d1 = std::abs(l.a * v.getX() + l.b * v.getY() + l.c);
        return d1 / d;
    }


    template<int size>
    inline double distance(const Vector& v, const Polygon<size>& p) {
        Line line = Line(p.vectors[p.vectors.size() - 1], p.vectors[0]);
        double distance = line.distance(v);

        for (int i = 0; i < p.vectors.size() - 1; ++i) {

            line = Line(p.vectors[i], p.vectors[i + 1]);

            double d = line.distance(v);

            if (d < distance) {
                distance = d;
            }
        }

        return distance;
    }

    template<>
    inline double distance(const Vector& v, const Circle& c) {
        auto d = (v - c.center);
        return d.length();
    }

    template<>
    inline double distance(const Line& l, const Vector& v) {
        return distance(v, l);
    }

    template<>
    inline double distance(const Line& l, const Circle& c) {
        return distance(l, c.center);
    }


    template<int size>
    inline double distance(const Polygon<size>& p, const Vector& v) {
        Line line{p.vectors[p.vectors.size() - 1], p.vectors[0]};
        double distance = line.distance(v);

        for (int i = 0; i < p.vectors.size() - 1; ++i) {

            line = Line(p.vectors[i], p.vectors[i + 1]);

            double d = line.distance(v);

            distance = std::min(d, distance);
        }

        return distance;
    }

    template<int size>
    inline double distance(const Polygon<size>& p, const Circle& c) {
        return distance(p, c.center);
    }

    template<>
    inline double distance(const Circle& c1, const Circle& c2) {
        return distance(c1.center, c2.center);
    }


    template<>
    inline double distance(const Circle& c, const Line& l) {
        auto v = l.nearestVector(c.center);
        return distance(v, c);
    }


    template<int size>
    inline double distance(const Circle& c, const Polygon<size>& p) {
        return distance(p, c);
    }


    template<>
    inline double distance(const Circle& c, const Vector& v) {
        return distance(v, c);
    }

    template <typename T1, typename T2>
    inline double distance(const T1&, const T2&) {
        std::stringstream errStr;
        errStr << "distance for ";
        errStr << typeid(T1).name();
        errStr << " and ";
        errStr << typeid(T2).name();
        errStr << " is not implemented";
        throw std::runtime_error(errStr.str());
    }

    template<int size>
    inline bool contains(const Polygon<size>& p, const Vector& v) {
        int count = 0;

        Vector rayEnd(p.maxX + 1, v.getY());

        Line ray{v, rayEnd};

        Line line{p.vectors[p.vectors.size() - 1], p.vectors[0]};
        count += line.intersect(ray);

        for (int i = 0; i < p.vectors.size() - 1; ++i) {

            line = Line{p.vectors[i], p.vectors[i + 1]};
            count += line.intersect(ray);
        }

        return count % 2 != 0;
    }


    template<int size>
    inline bool contains(const Polygon<size>& p, const Line& l) {
        return !l.infinite && contains(p, l.from) && contains(p, l.to);
    }


    template<int size1, int size2>
    inline bool contains(const Polygon<size1>& p1, const Polygon<size2>& p2) {
        for (Vector v: p2.vectors) {
            if (!contains(p1, v)) {
                return false;
            }
        }

        return true;

    }


    template<int size>
    inline bool contains(const Polygon<size>& p, const Circle& c) {
        int count = 0;
        Line l{p.vectors[p.vectors.size() - 1], p.vectors[0]};
        count += c.intersect(l);

        for (int i = 0; i < p.vectors.size() - 1; ++i) {

            l = Line{p.vectors[i], p.vectors[i + 1]};

            count += c.intersect(l);
        }

        return count == 0 && contains(p, c.center);
    }

    template<>
    inline bool contains(const Circle& c, const Vector& v) {

        return distance(c, v) <= c.radius;
    }


    template<>
    inline bool contains(const Circle& c, const Line& l) {
        return !l.infinite && contains(c, l.from) && contains(c, l.to);
    }


    template<>
    inline bool contains(const Circle& p1, const Circle& p2) {
        return distance(p1, p2) + p2.radius < p1.radius;
    }

    template <typename T1, typename T2>
    inline bool contains(const T1&, const T2&) {
        std::stringstream errStr;
        errStr << "contains for ";
        errStr << typeid(T1).name();
        errStr << " and ";
        errStr << typeid(T2).name();
        errStr << " is not implemented";
        throw std::runtime_error(errStr.str());
    }

    template<int size>
    inline bool contains(const Circle& c, const Polygon<size>& p) {
        int count = 0;
        Line l{p.vectors[p.vectors.size() - 1], p.vectors[0]};
        count += c.intersect(l);

        for (int i = 0; i < p.vectors.size() - 1; ++i) {

            l = Line{p.vectors[i], p.vectors[i + 1]};

            count += c.intersect(l);
        }

        for (auto vec : p.vectors) {
            count += !c.intersect(l);
        }

        return count == 0;
    }

};