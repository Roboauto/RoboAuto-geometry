//
// Created by Martin Miksik on 30/05/2018.
//

#pragma once

namespace GeometryMath {
    template<class T1, class T2>
    double distance(const T1&, const T2&);

    template<class T1, class T2>
    bool contains(const T1&, const T2&);


    class DistanceTrait {
    public:
        template<class T>
        double distance(const T& object) const {
            return GeometryMath::distance(*this, object);
        }
    };


    class ContainsTrait {
    public:
        template<class T>
        bool contains(const T& object) const {
            return GeometryMath::contains(*this, object);
        }
    };

};
