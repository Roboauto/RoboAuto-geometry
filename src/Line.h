//
// Created by Martin Miksik on 22/05/2018.
//

#pragma once

#include <stdexcept>
#include "Drawer.h"

#include "Vector.h"

class Line : public Drawable, public GeometryMath::DistanceTrait {
public:
    Line(const Vector& _from, const Vector& _to, bool _infinite = false) : from(_from),
                                                                           to(_to),
                                                                           a(_from.getY() - _to.getY()),
                                                                           b(_to.getX() - _from.getX()),
                                                                           c(-b * _from.getY() + -a * _from.getX()),
                                                                           infinite(_infinite) {};


    Vector direction() const {
        return (to - from) / length();
    }


#ifdef QT_DRAW
    QAbstractSeries *draw( std::string name ) override
    {
        auto *series = new QLineSeries();
        series->append( from.x, from.y );
        series->append( to.x, to.y );

        series->setName( name.c_str() );
        return series;
    }
#endif


    //TODO: Tests
    double length() const {
        return from.distance(to);
    }


    bool intersect(const Line& line) const {
        Orientation o1 = orientation(line.from);
        Orientation o2 = orientation(line.to);

        Orientation o3 = line.orientation(from);
        Orientation o4 = line.orientation(to);

        return (o1 != o2 && o3 != o4) || (o1 == Orientation::collinear && onSegment(line.from)) || (o2 == Orientation::collinear && onSegment(line.from))
        || (o3 == Orientation::collinear && onSegment(line.to)) || (o4 == Orientation::collinear && onSegment(line.to));
    }


    Vector intersection(const Line& line) {
        //TODO: Line line is infinite?
        if (((!infinite && !intersect(line)) && (!line.infinite && !line.intersect(Line{from, to}))) ||
                isParallel(line)) {
            //TODO: Exception
            throw std::invalid_argument("Lines do not intersect");
        }

        double x = (b * line.c - line.b * c) / (a * line.b - line.a - b);
        double y = (line.a * c - a * line.c) / (a * line.b - line.a - b);

        return {x, y};
    }


    Vector nearestVector(const Vector& vector) const {
        return infinite ? nearestVectorOnLine(vector) : nearestVectorOnLineSegment(vector);
    }


    bool isParallel(const Line& line) const {
        return (-a / b) == (-line.a / b);
    }


    bool isPerpendicular(const Line& line) const {
        return (-a / b) * (-line.a / b) == -1;
    }


    bool onSegment(const Vector& v) const {
        //TODO: Near float
        return segmentDistance(v) < PRECISION;
    }


    Line reverse() {
        return {to, from};
    }


    double segmentDistance(const Vector& vector) const {
        const Vector segment = nearestVectorOnLineSegment(vector);
        Vector diff = vector - segment;
        return diff.length();
    }


    bool operator==(const Line& line) const {
        return to == line.to && from == line.from;
    }


    bool operator!=(const Line& line) const {
        return to != line.to || from != line.from;
    }


    Vector from;
    Vector to;

    double a;
    double b;
    double c;

    bool infinite;

private:

    enum Orientation {
        collinear = 0,
        clockWise,
        counterClockWise
    };


    Orientation orientation(const Vector& v) const {
        double val = ((to.getY() - from.getY()) * (v.getX() - to.getX())) - ((to.getX() - from.getX()) * (v.getY() - to.getY()));
        if (val == 0) { return Orientation::collinear; }

        return (val > 0) ? Orientation::clockWise : Orientation::counterClockWise;
    }


    Vector nearestVectorOnLine(const Vector& vector) const {
        double x = (-a * b * vector.getY() + b * b * vector.getX() - a * c) / (b * b + a * a);
        double y = (a * a * vector.getY() - a * b * vector.getX() - b * c) / (b * b + a * a);

        return {x, y};
    }


    Vector nearestVectorOnLineSegment(const Vector& vector) const {
        Vector nearest = nearestVectorOnLine(vector);

        if (nearest == vector && (nearest - to).length() < length() && (nearest - from).length() < length()) {
            return nearest;
        }

        Line p{nearest, vector};

        auto oFrom = p.orientation(from);
        auto oTo = p.orientation(to);


        if (oFrom != oTo || vector.distance(from) == vector.distance(to)) {
            return nearest;
        }
        if (vector.distance(from) < vector.distance(to)) {
            return from;
        }

        return to;

    }
};