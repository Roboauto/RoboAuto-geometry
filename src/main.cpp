//#define QT_DRAW

#include <iostream>
#include "Vector.h"
#include "Line.h"
#include "Polygon.h"
#include "Circle.h"
#include "Drawer.h"


#ifdef QT_DRAW
#include <QtCharts>
using namespace QtCharts;
#endif


int main( int argc, char *argv[] )
{
#ifdef QT_DRAW
	QApplication application( argc, argv );
#endif
	Vector O{ 0, 0 };

	Vector A{ 1, 1 };
	Vector B{ -1.7, 1 };
	Vector C{ 5, 5 };

	Vector K{ 2, 2 };
	Vector L{ 0, 2 };
	Vector M{ 0, 0 };
	Vector N{ 2, 0 };

	Vector F{ 3, 3.3 };
	Vector R{ 1.5, 3.6 };

	Vector Q{ 4, 4 };
	Vector W{ 3, 3 };
	Vector E{ -1, 4 };
	Vector T{ 0, 2 };
	Vector U{ -1, 0 };
	Vector I{ 3, 1 };



	std::array < Vector, 4 > point = { K, L, M, N };
	std::array < Vector, 6 > pointl = { Q, W, E, T, U, I };


//	Vector W{ 1, 1 };

	Polygon < 4 > o( point );
	Polygon < 6 > l( pointl );

	auto pol = o.addVector(A, 0);


//	Drawer::draw(o, "o");
//	Drawer::draw(l,"l");
#ifdef QT_DRAW
	Drawer::draw(pol, "pol");
	Drawer::show();
	return application.exec();
#endif
}

