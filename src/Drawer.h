//
// Created by Martin Miksik on 23/05/2018.
//

#pragma once

#ifdef QT_DRAW
#include <QtCharts>
#include "Drawable.h"
using namespace QtCharts;
#endif
#include <string>

class Drawer {
private:
#ifdef QT_DRAW
    Drawer( ) : chart( new QChart() ) { };
#else

    Drawer();

#endif

public:
#ifdef QT_DRAW
    static void draw( Drawable &series, std::string name = "" )
    {
        getInstance()->chart->addSeries( series.draw( name ) );
    }


    static void show( )
    {
        auto instance = getInstance();
        auto *chartView = new QChartView( instance->chart );

        chartView->setRenderHint( QPainter::Antialiasing );
        chartView->setRubberBand( QChartView::RectangleRubberBand );

        instance->chart->setTitle( "Data" );
        instance->chart->createDefaultAxes();
        instance->chart->axisX()->setRange( -10, 10 );
        instance->chart->axisY()->setRange( -10, 10 );

        instance->window = new QMainWindow();
        instance->window->setCentralWidget( chartView );
        instance->window->resize( 600, 600 );
        instance->window->show();
    }
#else


    template<class T>
    static void draw(T& series, std::string name = "") {}


    static void show() {}


#endif

private:
    static Drawer* getInstance() {
        static auto instance = new Drawer();
        return instance;
    }


#ifdef QT_DRAW
    QChart *chart;
    QMainWindow *window;
#endif
};



