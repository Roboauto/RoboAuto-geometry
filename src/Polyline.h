#pragma once

#include "Geometry.h"
#include "Vector.h"
#include <vector>

class Polyline : public GeometryMath::DistanceTrait {
public:
    Polyline() = default;

    Polyline(const std::vector<Vector>& pts) {
        from = pts.front();
        to = pts.back();

        points = pts;
    }

    // distance

    void insertPointIntoSegment(const int segmentId, const Vector& pt) {}

private:
    std::vector<Vector> points{};
    Vector from{};
    Vector to{};
};