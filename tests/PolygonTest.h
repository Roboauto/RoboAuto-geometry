//
// Created by Martin Miksik on 24/05/2018.
//

#pragma once

#include "../src/Vector.h"
#include "gtest/gtest.h"
#include "../src/Polygon.h"


TEST( Polygon, contains )
{
	Vector K{ 2, 2 };
	Vector L{ 4, 2 };
	Vector M{ 4, 4 };
	Vector N{ 2, 4 };

	Vector Q{ 4, 4 };
	Vector W{ 3, 3 };
	Vector E{ -1, 4 };
	Vector T{ 0, 2 };
	Vector U{ -1, 0 };
	Vector I{ 3, 1 };

	Vector F{ 3, 3.3 };
	Vector B{ -1.7, 1 };

	std::array < Vector, 4 > point = { K, L, M, N };
	std::array < Vector, 6 > pointl = { Q, W, E, T, U, I };

	Polygon < 4 > o( point );
	Polygon < 6 > l( pointl );

	ASSERT_EQ( o.distance( B ), 2);

	ASSERT_EQ( o.contains( B ), false );
	ASSERT_EQ( o.contains( F ), true );
	ASSERT_EQ( l.contains( F ), false );
}


TEST( Polygon, rotate )
{
	Vector K{ 0, 0 };
	Vector L{ 4, 0 };
	Vector M{ 0, 4 };

	Vector L2{ -4, 0 };

	std::array < Vector, 3 > vectors = { K, L, M };

	Polygon < 3 > t( vectors );

	auto r = t.rotate( M_PI_2 );

	ASSERT_EQ( K, r.vectors[ 0 ] );

	ASSERT_NEAR( M.x, r.vectors[ 1 ].x, PRECISION );
	ASSERT_NEAR( M.y, r.vectors[ 1 ].y, PRECISION );

	ASSERT_NEAR( L2.x, r.vectors[ 2 ].x, PRECISION );
	ASSERT_NEAR( L2.y, r.vectors[ 2 ].y, PRECISION );
}