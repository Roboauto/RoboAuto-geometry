//
// Created by Martin Miksik on 30/05/2018.
//

#pragma once

namespace GeometryMath {
	template < class T1, class T2 >
	double distance( T1&, T2& );

	template < class T1, class T2 >
	bool contains( T1&, T2& );


	class DistanceTrait
	{
	public:
		template < class T >
		double distance( T& object ) const
		{
			return GeometryMath::distance( * this, object );
		}
	};


	class ContainsTrait
	{
	public:
		template < class T >
		bool contains( T& object ) const
		{
			return GeometryMath::contains( * this, object );
		}
	};

};