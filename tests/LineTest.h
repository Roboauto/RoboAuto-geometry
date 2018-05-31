//
// Created by Martin Miksik on 24/05/2018.
//

#pragma once

#include <gtest/gtest.h>
#include "../src/Vector.h"
#include "../src/Line.h"

TEST( Line, distance )
{
	Vector A( 1, 0 );
	Vector B( 0, 1 );
	Vector C( 1, 1 );

	Line p{ A, B };
	double i = p.distance( C );
	ASSERT_NEAR( p.distance( C ), 1.41421 / 2, PRECISION ) << p.distance( C );
}


TEST( Line, intersect )
{
	Vector A( 0, 0 );
	Vector B( 1, 1 );

	Vector C( -1, 1 );
	Vector D( 1, 0 );

	Line p{ A, B };
	Line u{ C, D };

	ASSERT_EQ( p.intersect( u ), true );
}


TEST( Line, intersection )
{
	Vector A( 0, 0 );
	Vector B( 2, 2 );

	Vector C( 0, 2 );
	Vector D( 2, 0 );

	Line p{ A, B };
	Line u{ C, D };

	Vector I( 1, 1 );

	ASSERT_EQ( p.intersection( u ), I );
}


TEST( Line, isParaller )
{
	Vector A( 0, 0 );
	Vector B( 1, 1 );

	Vector C( -1, 0 );
	Vector D( 0, 1 );

	Line p{ A, B };
	Line u{ C, D };

	ASSERT_EQ( p.isParaller( u ), true );
}


TEST( Line, isPerpendicular )
{
	Vector A( 0, 0 );
	Vector B( 1, 1 );

	Vector D( -1, -1 );

	Line p{ A, B };
	Line u{ A, D };

	ASSERT_EQ( p.isPerpendicular( u ), true );
}


TEST( Line, nearestVectorOnLine )
{
	Vector A( 0, 0 );
	Vector B( 1, 1 );

	Vector C( 1, 3 );
	Vector N( 2, 2 );

	Line p{ A, B, true};

	ASSERT_EQ( p.nearestVector( C ), N );
}


TEST( Line, nearestVectorOnLineSegment )
{
	Vector A( 0, 0 );
	Vector B( 1, 1 );

	Vector C( 1, 3 );
	Vector N( 1, 1 );

	Vector X( 0, 1 );
	Vector Q( 0.5, 0.5 );

	Line p{ A, B };


	Vector K( 1, 0 );
	Vector L( 0, 1 );

	Vector Y( 0, 2 );

	Line u{ K, L };


	Vector S( 0, 0 );
	Vector D( 1, 0 );

	Vector Z( 0.5, 1 );
	Vector SDC( 0.5, 0 );

	Line s{ S, D };
	Line d{ D, S };

	ASSERT_EQ( p.nearestVector( C ), N );
	ASSERT_EQ( p.nearestVector( X ), Q );

	ASSERT_EQ( u.nearestVector( Y ), L );

	ASSERT_EQ( s.nearestVector( Z ), SDC );
	ASSERT_EQ( d.nearestVector( Z ), SDC );
}


TEST( Line, normalVector )
{
	Vector A( 4, 2 );
	Vector R( 4, -2 );

	ASSERT_EQ( A.normalVector(), R );
}


TEST( Line, onSegment )
{
	Vector A( 0, 0 );
	Vector B( 1, 1 );

	Vector X( 2, 5 );
	Vector Q( 0.5, 0.5 );

	Line p{ A, B };

	ASSERT_EQ( p.onSegment( X ), false );
	ASSERT_EQ( p.onSegment( Q ), true );
}


TEST( Line, reverse )
{
	Vector A( 2, 4 );
	Vector B( 4, 2 );

	Line p{ A, B };
	Line r{ B, A };
	ASSERT_EQ( p.reverse(), r );
}


TEST( Line, segmentDistance )
{
	Vector A( 1, 0 );
	Vector B( 0, 1 );

	Vector Y( 0, 2 );
	Vector O( -1, 2 );

	Line p{ A, B };

	ASSERT_NEAR( p.segmentDistance( Y ), 1, PRECISION );
	ASSERT_NEAR( p.segmentDistance( O ), 1.4142171, PRECISION );
}


