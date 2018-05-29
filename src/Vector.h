//
// Created by Martin Miksik on 21/05/2018.
//

#pragma once

#include <cmath>
#include <sstream>
#include <QScatterSeries>
#include "Drawable.h"

enum Axe
{
	x = 0,
	y,
};

class Vector : public Drawable
{
public:
	Vector( double _x, double _y ) : x( _x ), y( _y ) { };


	double alpha( )
	{
		return atan2( y, x );
	}


	//TODO: Check
	double angleWith( Vector& vector )
	{
		return abs( alpha() - vector.alpha() );
	}


	double crossProduct( Vector& vector )
	{
		return x * vector.y - y * vector.x;
	}


	double distance( Vector vector )
	{
		return sqrt( pow( vector.x - x, 2 ) + pow( vector.y - y, 2 ) );
	}


	QAbstractSeries *draw( std::string name ) override
	{
		auto *point = new QScatterSeries();

		point->setMarkerShape( QScatterSeries::MarkerShapeCircle );
		point->setMarkerSize( 10.0 );

		point->append( x, y );
		point->setName( name.c_str() );

		return point;
	}


	double length( )
	{
		return sqrt( pow( x, 2 ) + pow( y, 2 ) );
	}


	Vector normalVector( )
	{
		return { x, -y };
	}


//	Vector rotate( double radian )
//	{
//		double s = sin( radian );
//		double c = cos( radian );
//
//		return {
//				x * c + y * s,
//				-x * s + y * c
//		};
//	}


	Vector rotate( double radian, Vector center = { 0, 0 } )
	{
		double s = sin( radian );
		double c = cos( radian );

		double nx = x - center.x;
		double ny = y - center.y;

		return {
				( nx * c - ny * s ) + center.x,
				( nx * s + ny * c ) + center.y
		};
	}


	bool operator==( Vector vector ) const
	{
		return x == vector.x && y == vector.y;
	}


	bool operator!=( Vector vector ) const
	{
		return x != vector.x || y != vector.y;
	}


	Vector operator!( ) const
	{
		return { -x, -y };
	}


	Vector operator+( Vector vector ) const
	{
		return { x + vector.x, y + vector.y };
	}


	double operator+( double i )
	{
		return length() + i;
	}


	Vector operator-( Vector vector ) const
	{
		return { x - vector.x, y - vector.y };
	}


	double operator-( double i )
	{
		return length() - i;
	}


	Vector operator*( double i ) const
	{
		return { i * x, i * y };
	}


	double operator*( Vector vector ) const
	{
		return x * vector.x + y * vector.y;
	}


	//TODO: Tests
	double operator/( Vector vector ) const
	{
		return x / vector.x + y / vector.y;
	}


	Vector operator/( double i ) const
	{
		return { x / i, y / i };
	}


	explicit operator std::string( ) const
	{
		return "[" + std::to_string( x ) + "," + std::to_string( y ) + "]";
	}


	double x;
	double y;
};