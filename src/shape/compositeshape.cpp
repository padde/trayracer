#include "compositeshape.hpp"

// project header
#include <box.hpp>
#include <iostream>



CompositeShape::CompositeShape ( std::string name ) :
	Shape(name)
{}

/* virtual */
CompositeShape::~CompositeShape ()
{}

bool
CompositeShape::hit ( const Ray& ray, interval_t& tmin, HitRecord& hitrec ) const
{
	bool is_hit = false;
	HitRecord tmprec(hitrec);
	
	// check bbox first
	float tmin_bbox = 0;
	// if ( ! Shape::bbox().hit(ray,tmin_bbox,tmprec) )
	// 	{
	// 		return false;
	// 	}
	// go through all shapes and check for hits
	for ( unsigned i=0; i < shapes_.size(); ++i )
	{
		if ( shapes_[i]->hit(ray, tmin, tmprec) )
		{
			is_hit = true;
		}
	}
	
	// we don't want to change the original hitrec for every shape,
	// so we only store the values there once to save time
	if ( is_hit )
		hitrec = tmprec;
	
	return is_hit;
}

bool
CompositeShape::hit ( const Ray& ray, interval_t& tmin ) const
{
	// go through all shapes and check for hits
	for ( unsigned i=0; i < shapes_.size(); ++i )
		if ( shapes_[i]->hit(ray, tmin) )
			return true;
	
	return false;
}

void
CompositeShape::push ( Shape* shape )
{
	shapes_.push_back(shape);
	
	float min_x = std::min( shape->bbox().a()[0], bbox_.first[0] );
	float min_y = std::min( shape->bbox().a()[1], bbox_.first[1] );
	float min_z = std::min( shape->bbox().a()[2], bbox_.first[2] );
	float max_x = std::max( shape->bbox().b()[0], bbox_.second[0] );
	float max_y = std::max( shape->bbox().b()[1], bbox_.second[1] );
	float max_z = std::max( shape->bbox().b()[2], bbox_.second[2] );
	
	bbox_.first  = Point(min_x,min_y,min_z);
	bbox_.second = Point(max_x,max_y,max_z);
}

void
CompositeShape::transform ( const Matrix& trans )
{
	for ( unsigned i=0; i < shapes_.size(); ++i )
		shapes_[i]->transform(trans);
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
