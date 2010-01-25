// system header
#include <UnitTest++.h>
#include <sstream>

// project header
#include "vector.hpp"
#include "point.hpp"

TEST ( vector__standard_constructor )
{
	Vector v;
	
	CHECK_EQUAL(0.0f, v[0]);
	CHECK_EQUAL(0.0f, v[1]);
	CHECK_EQUAL(0.0f, v[2]);
}

TEST ( vector__copy_constructor )
{
	Vector v(1.0, 2.0, 3.0);
	Vector w(v);
	
	CHECK_EQUAL(1.0f, v[0]);
	CHECK_EQUAL(2.0f, v[1]);
	CHECK_EQUAL(3.0f, v[2]);
}

TEST ( vector__one_point_constructor )
{
	Point p(1,2,3);
	Vector v(p);
	
	CHECK_EQUAL(1.0f, v[0]);
	CHECK_EQUAL(2.0f, v[1]);
	CHECK_EQUAL(3.0f, v[2]);
}

TEST ( vector__two_points_constructor )
{
	Point p(1,2,3);
	Point q(3,4,5);
	Vector v(p,q);
	
	CHECK_EQUAL(-2.0f, v[0]);
	CHECK_EQUAL(-2.0f, v[1]);
	CHECK_EQUAL(-2.0f, v[2]);
}

TEST ( vector__index_operator )
{
	Vector v(1,2,3);
	
	CHECK_EQUAL(1.0f, v[0]);
	CHECK_EQUAL(2.0f, v[1]);
	CHECK_EQUAL(3.0f, v[2]);
}

TEST ( vector__const_index_operator )
{
	const Vector v(1,2,3);
	
	CHECK_EQUAL(1.0f, v[0]);
	CHECK_EQUAL(2.0f, v[1]);
	CHECK_EQUAL(3.0f, v[2]);
}

TEST ( vector__should_compute_length )
{
	Vector v(1,2,3);
	
	CHECK_CLOSE(3.7416574f, v.length(), 0.0000001);
}

TEST ( vector__should_make_unit_vector )
{
	Vector v(5,6,7);
	
	v.unify();
	
	CHECK_EQUAL(1.0f, v.length());
}

TEST ( vector__assignment_operator )
{
	Vector v(5,6,7);
	Vector w = v;
	
	CHECK_EQUAL(5.0f, w[0]);
	CHECK_EQUAL(6.0f, w[1]);
	CHECK_EQUAL(7.0f, w[2]);
}

TEST ( vector__unary_plus_operator )
{
	Vector v(1,1,1);
	Vector w(1,2,3);
	
	v += w;
	
	CHECK_EQUAL(2.0f, v[0]);
	CHECK_EQUAL(3.0f, v[1]);
	CHECK_EQUAL(4.0f, v[2]);
}

TEST ( vector__unary_minus_operator )
{	
	Vector v(1,2,3);
	Vector w(1,1,1);
	
	v -= w;
	
	CHECK_EQUAL(0.0f, v[0]);
	CHECK_EQUAL(1.0f, v[1]);
	CHECK_EQUAL(2.0f, v[2]);
}

TEST ( vector__unary_multiplication_operator )
{
	Vector v(1,2,3);
	
	v *= 1.5f;
	
	CHECK_EQUAL(1.5f, v[0]);
	CHECK_EQUAL(3.0f, v[1]);
	CHECK_EQUAL(4.5f, v[2]);
}

TEST ( vector__unary_division_operator )
{
	Vector v(3,4,7);
	
	v /= 2.0f;
	
	CHECK_EQUAL(1.5f, v[0]);
	CHECK_EQUAL(2.0f, v[1]);
	CHECK_EQUAL(3.5f, v[2]);
}

TEST ( vector__point_assignment_operator )
{
	Point p(6,7,8);
	Vector v = p;
	
	CHECK_EQUAL(6.0f, v[0]);
	CHECK_EQUAL(7.0f, v[1]);
	CHECK_EQUAL(8.0f, v[2]);
}

TEST ( vector__should_swap )
{
	Vector v(1,2,3);
	Vector w(5,6,7);
	
	v.swap(w);
	
	CHECK_EQUAL(5.0f, v[0]);
	CHECK_EQUAL(6.0f, v[1]);
	CHECK_EQUAL(7.0f, v[2]);
	
	CHECK_EQUAL(1.0f, w[0]);
	CHECK_EQUAL(2.0f, w[1]);
	CHECK_EQUAL(3.0f, w[2]);
}

TEST ( should__print_on_ostream )
{
	Vector v(1.2, 3.4, 5.6);
	std::stringstream ss(std::stringstream::out);
	v.print_on(ss);
	CHECK_EQUAL("Vector (1.2,3.4,5.6)", ss.str());
}

TEST ( vector__binary_plus_operator )
{
	Vector v(1,1,1);
	Vector w(1,2,3);
	
	Vector x = v + w;
	
	CHECK_EQUAL(2.0f, x[0]);
	CHECK_EQUAL(3.0f, x[1]);
	CHECK_EQUAL(4.0f, x[2]);
}

TEST ( vector__binary_minus_operator )
{
	Vector v(1,2,3);
	Vector w(1,1,1);
	
	Vector x = v - w;
	
	CHECK_EQUAL(0.0f, x[0]);
	CHECK_EQUAL(1.0f, x[1]);
	CHECK_EQUAL(2.0f, x[2]);
}

TEST ( vector__binary_multiplication_operator )
{
	Vector v(1,2,3);
	
	Vector w = v * 1.5f;
	
	CHECK_EQUAL(1.5f, w[0]);
	CHECK_EQUAL(3.0f, w[1]);
	CHECK_EQUAL(4.5f, w[2]);
}

TEST ( vector__binary_division_operator )
{
	Vector v(3,4,7);
	
	Vector w = v / 2.0f;
	
	CHECK_EQUAL(1.5f, w[0]);
	CHECK_EQUAL(2.0f, w[1]);
	CHECK_EQUAL(3.5f, w[2]);
}

TEST ( vector__equality_operator )
{
	Vector v(1,2,3);
	Vector w(1,2,3);
	
	CHECK(v == w);
}

TEST ( vector__unequality_operator )
{
	Vector v(1,2,3);
	Vector w(5,8,2);
	
	CHECK(v != w);
}

TEST ( vector__should_compute_dot_product )
{
	Vector v(1,2,3);
	Vector w(5,6,7);
	
	CHECK_EQUAL(38, dot(v,w) );
}

TEST ( vector__should_compute_cross_product )
{
	Vector v(1,2,3);
	Vector w(5,6,7);
	
	Vector x = cross(v,w);
	
	CHECK_EQUAL(-4.0f, x[0]);
	CHECK_EQUAL( 8.0f, x[1]);
	CHECK_EQUAL(-4.0f, x[2]);
}

