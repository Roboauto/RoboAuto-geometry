//
// Created by Martin Miksik on 23/05/2018.
//
#pragma once

#ifdef QT_DRAW
#include <QtCharts>
using namespace QtCharts;
#endif

class Drawable {
public:
#ifdef QT_DRAW
    virtual QAbstractSeries *draw( std::string name ) = 0;
#endif
};