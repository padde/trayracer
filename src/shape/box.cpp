// i/f header
#include "box.hpp"

// system header
#include <iostream>

// project header
#include <shape.hpp>

namespace {
	// internal stuff
	
	const double epsilon = 0.00000001;
	
	const Vector normals[6] = {
		Vector(-1, 0, 0), 
		Vector(0, -1, 0),
		Vector(0, 0, -1),
		Vector(1, 0, 0),
		Vector(0, 1, 0),
		Vector(0, 0, 1) };
}


Box::Box ()
{}

Box::Box ( const Point& a, const Point& b ) :
	a_(a), b_(b)
{}

Box::~Box ()
{}

bool
Box::hit ( const Ray& ray, interval_t tmin, interval_t tmax, HitRecord& hitrec ) const
{
	return false;
}

bool
Box::hit ( const Ray& ray, interval_t tmin, interval_t tmax ) const
{
	return false;
}
