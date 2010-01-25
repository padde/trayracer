// system header
#include <UnitTest++.h>
#include <sstream>

// project header
#include "point.hpp"
#include "vector.hpp"
#include "ray.hpp"


TEST ( ray__standard_constructor )
{
	Point p(0,0,0);
	Vector v(0,0,0);
	Ray r;
	
	CHECK_EQUAL(p, r.origin());
	CHECK_EQUAL(v, r.dir());
}

TEST ( ray__copy_constructor )
{
	Point p(4,2,1.6);
	Vector v(5,4,8);
	Ray r(p,v);
	Ray s(r);
	
	CHECK_EQUAL(p, s.origin());
	CHECK_EQUAL(v, s.dir());
}

TEST ( ray__verbose_constructor )
{
	Point p(12,3.1,9.2);
	Vector v(45,2,1.12);
	Ray r(p,v);
	
	CHECK_EQUAL(p, r.origin());
	CHECK_EQUAL(v, r.dir());
}

TEST ( ray__origin_getter )
{
	Point p(12,3.1,9.2);
	Vector v(45,2,1.12);
	Ray r(p,v);
	
	CHECK_EQUAL(p, r.origin());
}

TEST ( ray__origin_setter )
{
	Point p1(12,23.1,9.2);
	Point p2(9.3,3.2,9.9);
	Vector v(45,2.3,1.12);
	
	Ray r(p1,v);
	
	r.origin(p2);
	
	CHECK_EQUAL(p2, r.origin());
}

TEST ( ray__dir_getter )
{
	Point p(12,3.1,9.2);
	Vector v(45,2,1.12);
	Ray r(p,v);
	
	CHECK_EQUAL(v, r.dir());
}

TEST ( ray__dir_setter )
{
	Point p(12,23.1,9.2);
	Vector v1(3.1,7.1,1);
	Vector v2(8,7.1,2.4);
	
	Ray r(p,v1);
	
	r.dir(v2);
	
	CHECK_EQUAL(v2, r.dir());
}

TEST ( ray__should_compute_point_at_parameter )
{
	Point p(12,3.1,9.2);
	Vector v(45,2,1.12);
	Ray r(p,v);
	
	CHECK_CLOSE(237.0f, r.point_at_parameter(5)[0], 0.000001);
	CHECK_CLOSE( 13.1f, r.point_at_parameter(5)[1], 0.000001);
	CHECK_CLOSE( 14.8f, r.point_at_parameter(5)[2], 0.000001);
}

TEST ( ray__should_print_on_ostream )
{
	Point p(12,3.1,9.2);
	Vector v(45,2,1.12);
	Ray r(p,v);
	std::stringstream ss(std::stringstream::out);
	
	r.print_on(ss);
	
	CHECK_EQUAL("Ray ( Origin: Point (12,3.1,9.2), Direction: Vector (45,2,1.12) )", ss.str());
}


