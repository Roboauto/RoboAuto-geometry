//
// Created by Martin Miksik on 24/05/2018.
//

#pragma once

#include "../src/Vector.h"
#include "../src/Circle.h"

#include "gtest/gtest.h"

TEST( Circle, contains )
{
	Vector A{ 1, 1 };
	Vector B{ 2, 2 };
	Vector N{ 2, 2.1 };

	Vector CA{ 0, 0 };
	Vector CB{ 65, 3 };

	Circle CirA{2, CA};
	Circle CirB{5, CB};

	ASSERT_EQ(CirA.contains(A), true);

	ASSERT_EQ(CirA.contains(B), false);

	ASSERT_EQ(CirA.contains(N), false);
	ASSERT_EQ(CirB.contains(A), false);
}



TEST( Circle, distance )
{
	Vector C{ 0, 0 };
	Vector A{ 0, 2 };

	Circle Cir{2, C};
	ASSERT_EQ(Cir.distance(A), 2) << Cir.distance(A);
}


TEST( Circle, intersect )
{
	Vector C{ 5, 5 };

	Vector A{ 0, 0 };
	Vector B{ 1, 1 };

	Vector D{ 6, 5 };

	Line u{A, B};
	Line p{A, D};

	Circle Cir{3, C};
	ASSERT_EQ(Cir.intersect(u), true);
	ASSERT_EQ(Cir.intersect(p), true);
}


TEST( Circle, intersection )
{
	Vector C{ 0, 0 };

	Vector A{ -2, -2 };
	Vector B{ 2, 2 };
	Line p{A, B};

	std::vector<Vector> v{};

	Circle Cir{1, C};
	ASSERT_EQ(Cir.intersection(p), v) << Cir.intersect(p);
}