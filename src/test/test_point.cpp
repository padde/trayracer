// system header
#include <UnitTest++.h>
#include <sstream>

// project header
#include "point.hpp"


TEST ( point__standard_constructor )
{
	Point p;
	
	CHECK_EQUAL(0.0f, p[0]);
	CHECK_EQUAL(0.0f, p[1]);
	CHECK_EQUAL(0.0f, p[2]);
}

TEST ( point__copy_constructor )
{
	Point p(1,2,3);
	Point q(p);
	
	CHECK_EQUAL(1.0f, q[0]);
	CHECK_EQUAL(2.0f, q[1]);
	CHECK_EQUAL(3.0f, q[2]);
}

// TEST ( point__vector_constructor )
// {
// 	Point p;
// 	
// 	CHECK_EQUAL(0.0f, p[x]);
// 	CHECK_EQUAL(0.0f, p[y]);
// 	CHECK_EQUAL(0.0f, p[z]);
// }

TEST ( point__value_t_constructor )
{
	Point p(1.1, 2.2, 3.3);
	
	CHECK_EQUAL(1.1f, p[0]);
	CHECK_EQUAL(2.2f, p[1]);
	CHECK_EQUAL(3.3f, p[2]);
}

TEST ( point__index_operator )
{
	Point p;
	
	p[0] = 1.2;
	p[1] = 3.4;
	p[2] = 5.6;
	
	CHECK_EQUAL(1.2f, p[0]);
	CHECK_EQUAL(3.4f, p[1]);
	CHECK_EQUAL(5.6f, p[2]);
}

TEST ( point__const_index_operator )
{
	const Point p(1.2, 3.4, 5.6);
	
	CHECK_EQUAL(1.2f, p[0]);
	CHECK_EQUAL(3.4f, p[1]);
	CHECK_EQUAL(5.6f, p[2]);
}

TEST ( point__unary_point_plus_operator )
{
	Point p(1.2, 3.4, 5.6);
	Point q(9.8, 7.6, 5.4);
	
	p += q;
	
	CHECK_EQUAL(11.0f, p[0]);
	CHECK_EQUAL(11.0f, p[1]);
	CHECK_EQUAL(11.0f, p[2]);
}

TEST ( point__unary_point_minus_operator )
{
	Point p(1.2, 3.4, 5.6);
	Point q(0.2, 2.4, 4.6);
	
	p -= q;
	
	CHECK_EQUAL(1.0f, p[0]);
	CHECK_EQUAL(1.0f, p[1]);
	CHECK_EQUAL(1.0f, p[2]);
}

TEST ( point__assignment_operator )
{
	Point p(1.2, 3.4, 5.6);
	Point q = p;
	
	CHECK_EQUAL(1.2f, p[0]);
	CHECK_EQUAL(3.4f, p[1]);
	CHECK_EQUAL(5.6f, p[2]);
}



// TEST ( point__unary_vector_plus_operator )
// {
// 	
// }

// TEST ( point__unary_vector_minus_operator )
// {
// 	
// }

TEST ( point__should_swap )
{
	Point p(1.2, 3.4, 5.6);
	Point q(0.2, 2.4, 4.6);
	
	p.swap(q);
	
	CHECK_EQUAL(0.2f, p[0]);
	CHECK_EQUAL(2.4f, p[1]);
	CHECK_EQUAL(4.6f, p[2]);
	
	CHECK_EQUAL(1.2f, q[0]);
	CHECK_EQUAL(3.4f, q[1]);
	CHECK_EQUAL(5.6f, q[2]);
}

TEST ( point__should_print_on_ostream )
{
	Point p(1.2, 3.4, 5.6);
	std::stringstream ss(std::stringstream::out);
	p.print_on(ss);
	CHECK_EQUAL("Point (1.2,3.4,5.6)", ss.str());
}

TEST ( point__binary_point_plus_operator )
{
	Point p(1.2, 3.4, 5.6);
	Point q(8.8, 6.6, 4.4);
	
	Point r = p + q;
	
	CHECK_EQUAL(10.0f, r[0]);
	CHECK_EQUAL(10.0f, r[1]);
	CHECK_EQUAL(10.0f, r[2]);
}

TEST ( point__binary_point_minus_operator )
{
	Point p(1.2, 3.4, 5.6);
	Point q(0.2, 2.4, 4.6);
	
	Point r = p - q;
	
	CHECK_EQUAL(1.0f, r[0]);
	CHECK_EQUAL(1.0f, r[1]);
	CHECK_EQUAL(1.0f, r[2]);
}

// TEST ( point__binary_vector_plus_operator )
// {
// 	
// }

// TEST ( point__binary_vector_minus_operator )
// {
// 	
// }

TEST ( point__equality_operator )
{
	Point p(1.2, 3.4, 5.6);
	Point q(1.2, 3.4, 5.6);
	
	CHECK(p == q);
}

TEST ( point__unequality_operator )
{
	Point p(1.2, 3.4, 5.6);
	Point q(7.8, 2.3, 5.1);
	
	CHECK(p != q);
}