//
// Created by Martin Miksik on 28/05/2018.
//

#pragma once

#include "Drawable.h"
#include "Vector.h"
#include "Line.h"

#include <cmath>

class Circle //: public Drawable
{
public:
	Circle( double _radius, Vector& _center ) : radius( _radius ), center( _center ) { };


	bool contains( Vector vector )
	{
		return distance( vector ) <= radius;
	}


	double distance( Vector vector )
	{
		Vector d = ( vector - center );
		return d.length();
	}


	bool intersect( Line ray )
	{
		return contains( ray.nearestVectorOnLine( center ) );
	}


	bool intersectLineSegment( Line lineSegment )
	{
		return contains( lineSegment.nearestVectorOnLineSegment( center ) );
	}


	std::vector < Vector > intersection( Line l )
	{
		Vector nearest = l.nearestVectorOnLine( center );
		double d = distance( nearest ); //lec
		std::vector < Vector > solutions = { };

		if ( d == radius ) {
			//1 solution
			solutions.push_back( nearest );

		} else if ( d < radius ) {
			// 2 solutions
			double t = ( center - l.from ) * l.direction();
			double dt = sqrt( radius * radius - d * d );

			Vector inter1 = ( l.direction() * ( t - dt ) ) + l.from;
			Vector inter2 = ( l.direction() * ( t + dt ) ) + l.from;

			solutions.push_back( inter1 );
			solutions.push_back( inter2 );

		}

		return solutions;
	}


	Vector center;
	double radius;

};