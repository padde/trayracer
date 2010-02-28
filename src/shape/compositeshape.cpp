// i/f header
#include "compositeshape.hpp"

// system header
#include <vector>
#include <iostream>

// project header
#include <ray.hpp>
#include <shape.hpp>


using namespace std;


CompositeShape::CompositeShape ()
{}

/* virtual */
CompositeShape::~CompositeShape ()
{}

bool
CompositeShape::hit ( const Ray& ray, interval_t tmin, interval_t tmax, HitRecord& hitrec ) const
{
	bool is_hit;
	HitRecord tmprec;
	
	// go through all shapes and check for hits
	for ( unsigned i=0; i < shapes_.size(); ++i )
	{
		if ( shapes_[i]->hit(ray, tmin, tmax, tmprec) )
		{
			tmax = tmprec.t;
			is_hit = true;
		}
	}
	
	// we don't want to change the original hitrec for every shape,
	// so we only store the values there once to save time
	if ( is_hit )
	{
		hitrec.hit    = tmprec.hit;
		hitrec.t      = tmprec.t;
		hitrec.color  = tmprec.color;
		hitrec.normal = tmprec.normal;
	}
	
	return is_hit;
}

bool
CompositeShape::hit ( const Ray& ray, interval_t tmin, interval_t tmax ) const
{
	bool is_hit(false);
	
	// go through all shapes and check for hits
	for ( unsigned i=0; i < shapes_.size(); ++i ) {
		if ( shapes_[i]->hit(ray, tmin, tmax) ) {
			is_hit = true;
		}
	}
	
	return is_hit;
}

void
CompositeShape::push ( Shape* shape )
{
	shapes_.push_back(shape);
}

void
CompositeShape::transform ( const Matrix& trans )
{
	for ( unsigned i=0; i < shapes_.size(); ++i ) {
		shapes_[i]->transform(trans);
	}
}

const Shape*
CompositeShape::operator[] ( unsigned index ) const
{
	return shapes_[index];
}

Shape*
CompositeShape::operator[] ( unsigned index )
{
	return shapes_[index];
}
