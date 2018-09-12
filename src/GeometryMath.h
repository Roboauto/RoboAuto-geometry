//
// Created by Martin Miksik on 29/05/2018.
//

#pragma once

#include<cmath>

#include "Vector.h"
#include "Line.h"
#include "Polygon.h"
#include "Circle.h"
#include "Polyline.h"

namespace GeometryMath {
	//
	// Distance from Vector to ...
	//

	template <>
	double distance( Vector& v1, Vector& v2 )
	{
		return std::sqrt( pow( v1.x - v2.x, 2 ) + pow( v1.y - v2.y, 2 ) );
	}


	template <>
	double distance( Vector& v, Line& l )
	{
		double d = std::sqrt( l.a * l.a + l.b * l.b );
		double d1 = std::abs( l.a * v.x + l.b * v.y + l.c );
		return d1 / d;
	}


	template < int size >
	double distance( Vector& v, Polygon < size >& p )
	{
		Line line = Line( p.vectors[ p.vectors.size() - 1 ], p.vectors[ 0 ] );
		double distance = line.distance( v );

		for ( int i = 0; i < p.vectors.size() - 1; ++i ) {

			line = Line( p.vectors[ i ], p.vectors[ i + 1 ] );

			double d = line.distance( v );

			if ( d < distance ) {
				distance = d;
			}
		}

		return distance;
	}


	template <>
	double distance( Vector& v, Circle& c )
	{
		auto d = ( v - c.center );
		return d.length();
	}

	//
	// Distance from line to ...
	//

	template <>
	double distance( Line& l, Vector& v )
	{
		return distance( v, l );
	}


	template <>
	double distance( Line& l1, Line& l2 )
	{
		throw std::invalid_argument( "Unimplemented" );
	}


	template < int size >
	double distance( Line& l, Polygon < size >& p )
	{
		throw std::invalid_argument( "Unimplemented" );
	}


	template <>
	double distance( Line& l, Circle& c )
	{
		return distance( l, c.center );
	}


	//
	// Distance from polygon to ...
	//

	template < int size >
	double distance( Polygon < size >& p, Vector& v )
	{
		Line line{ p.vectors[ p.vectors.size() - 1 ], p.vectors[ 0 ] };
		double distance = line.distance( v );

		for ( int i = 0; i < p.vectors.size() - 1; ++i ) {

			line = Line( p.vectors[ i ], p.vectors[ i + 1 ] );

			double d = line.distance( v );

//			if ( d < distance ) {
//				distance = d;
//			}
			distance = std::min( d, distance );
		}

		return distance;
	}


	template < int size >
	double distance( Polygon < size >& p, Line& l )
	{
		throw std::invalid_argument( "Unimplemented" );
	}


	template < int size1, int size2 >
	double distance( Polygon < size1 >& p1, Polygon < size2 >& p2 )
	{
		throw std::invalid_argument( "Unimplemented" );
	}


	template < int size >
	double distance( Polygon < size >& p, Circle& c )
	{
		return distance( p, c.center );
	}

	//
	// Distance from circle to ...
	//

	template <>
	double distance( Circle& c1, Circle& c2 )
	{
		return distance( c1.center, c1.center );
	}


	template <>
	double distance( Circle& c, Line& l )
	{
		auto v = l.nearestVector( c.center );
		return distance( v, c );
	}


	template < int size >
	double distance( Circle& c, Polygon < size >& p )
	{
		return distance( p, c );
	}


	template <>
	double distance( Circle& c, Vector& v )
	{
		return distance( v, c );
	}

	template <>
	bool distance( Polyline& p1, Polyline& p2 )
	{
		throw std::runtime_error("not implemented");
	}

	template <>
	bool distance( Polyline& p1, Vector& p2 )
	{
		throw std::runtime_error("not implemented");
	}

	//
	// Polygon contains ...
	//


	template < int size >
	bool contains( Polygon < size >& p, Vector& v )
	{

//		double x = v.x;
//		double y = v.y;

		int count = 0;

		Vector rayEnd( p.maxX + 1, v.y );

		Line ray{ v, rayEnd };

		Line line{ p.vectors[ p.vectors.size() - 1 ], p.vectors[ 0 ] };
		count += line.intersect( ray );

		for ( int i = 0; i < p.vectors.size() - 1; ++i ) {

			line = Line{ p.vectors[ i ], p.vectors[ i + 1 ] };
			count += line.intersect( ray );
		}

		return count % 2 != 0;
	}


	template < int size >
	bool contains( Polygon < size >& p, Line& l )
	{
		return !l.infinite && contains( p, l.from ) && contains( p, l.to );
	}


	template < int size1, int size2 >
	bool contains( Polygon < size1 >& p1, Polygon < size2 >& p2 )
	{
		for ( Vector v: p2.vectors ) {
			if ( !contains( p1, v ) ) {
				return false;
			}
		}

		return true;

	}


	template < int size >
	bool contains( Polygon < size >& p, Circle& c )
	{
		int count = 0;
		Line l{ p.vectors[ p.vectors.size() - 1 ], p.vectors[ 0 ] };
		count += c.intersect( l );

		for ( int i = 0; i < p.vectors.size() - 1; ++i ) {

			l = Line{ p.vectors[ i ], p.vectors[ i + 1 ] };

			count += c.intersect( l );
		}

		return count == 0 && contains( p, c.center );
	}

	//
	// Circle contains ...
	//


	template <>
	bool contains( Circle& c, Vector& v )
	{

		return distance( c, v ) <= c.radius;
	}


	template <>
	bool contains( Circle& c, Line& l )
	{
		return !l.infinite && contains( c, l.from ) && contains( c, l.to );
	}


	template <>
	bool contains( Circle& p1, Circle& p2 )
	{
		return distance( p1, p2 ) + p2.radius < p1.radius;
	}


	template < int size >
	bool contains( Circle& c, Polygon < size >& p )
	{
		int count = 0;
		Line l{ p.vectors[ p.vectors.size() - 1 ], p.vectors[ 0 ] };
		count += c.intersect( l );

		for ( int i = 0; i < p.vectors.size() - 1; ++i ) {

			l = Line{ p.vectors[ i ], p.vectors[ i + 1 ] };

			count += c.intersect( l );
		}

		for ( auto vec : p.vectors ) {
			count += !c.intersect( l );
		}

		return count == 0;
	}
};