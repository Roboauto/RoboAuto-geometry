//
// Created by Martin Miksik on 24/05/2018.
//

#pragma once

#include "../src/Vector.h"
#include "gtest/gtest.h"

#define PRECISION 0.0001

TEST( Vector, alpha )
{
	Vector A{ 1, 1 };

	ASSERT_FLOAT_EQ( M_PI_4, A.alpha() );

}


TEST( Vector, angleWith )
{
	Vector A{ 0, 1 };
	Vector B{ 1, 0 };
	Vector C{ 1, 1 };
	Vector E{ -1, 1 };

	double a = A.angleWith( B );
	double d = A.angleWith( C );

	double e = B.angleWith( E );


	ASSERT_NEAR( M_PI_2, a, PRECISION );
	ASSERT_NEAR( M_PI_4, d, PRECISION );
	ASSERT_NEAR( M_PI * 3 / 4, e, PRECISION );
}


TEST( Vector, crossProduct )
{
	Vector B{ 4, 3 };
	Vector A{ 3, 4 };

	ASSERT_FLOAT_EQ( B.crossProduct( A ), 4 * 4 - 3 * 3 );
}


TEST( Vector, distance )
{
	Vector A{ 1, 1 };
	Vector B{ 2, 2 };

	Vector C{ 0, 1 };

	ASSERT_FLOAT_EQ( 1.4142135, A.distance( B ) );
	ASSERT_FLOAT_EQ( 1.4142135, B.distance( A ) );

	ASSERT_FLOAT_EQ( 0, B.distance( B ) );
	ASSERT_FLOAT_EQ( 1, A.distance( C ) );
}


TEST( Vector, lenght )
{
	Vector B{ 1, 1 };

	ASSERT_FLOAT_EQ( 1.4142135, B.length() );
}


TEST( Vector, rotate )
{
	Vector A{ 1, 0 };
	Vector D = A.rotate( M_PI );

	Vector B{ 1, 1 };
	Vector R = B.rotate( M_PI_2 );
//	Vector R{ -1, -1 };
	
	ASSERT_NEAR( -1, D.x, PRECISION ) << D.x;
	ASSERT_NEAR( 0, D.y, PRECISION ) << D.y;

	ASSERT_NEAR( -1, R.x, PRECISION ) << R.x;
	ASSERT_NEAR( 1, R.y, PRECISION ) << R.y;
}


TEST( Vector, rotateAround )
{
	Vector A{ 1, 1 };
	Vector C{ 0, 1 };

	Vector D = A.rotate( M_PI, C );


	ASSERT_NEAR( -1, D.x, PRECISION );
	ASSERT_NEAR( 1, D.y, PRECISION );
}


TEST( Vector, equality )
{
	Vector A{ 2, 2 };
	Vector B{ 2, 2 };
	Vector C{ 3, 2 };

	ASSERT_EQ( A, B );
	ASSERT_NE( A, C );
}


TEST( Vector, negation )
{
	Vector A{ 2, 2 };
	Vector B{ -2, -2 };

	ASSERT_EQ( !A, B );
}


TEST( Vector, add )
{
	Vector A{ 2, 2 };
	Vector B{ 1, 2 };
	Vector C{ 1, 1 };

	Vector R{ 3, 4 };

	ASSERT_EQ( A + B, R );
	ASSERT_NEAR( C + 1, 2.41421, PRECISION );
}


TEST( Vector, substract )
{
	Vector A{ 2, 2 };
	Vector B{ 1, 2 };
	Vector C{ 1, 1 };

	Vector R{ 1, 0 };

	ASSERT_EQ( A - B, R );
	ASSERT_NEAR( C - 1, 0.41421, PRECISION );
}


TEST( Vector, multiply )
{
	Vector A{ 2, 2 };
	Vector B{ 3, 2 };

	Vector R{ 6, 6 };

	ASSERT_EQ( A * B, 10 );
	ASSERT_EQ( A * 3, R );
}


TEST( Vector, toString )
{
	Vector A{ 2, 5 };

	ASSERT_EQ( std::string(A), "[2.000000,5.000000]" );
}
