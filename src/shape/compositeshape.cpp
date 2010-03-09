#include "compositeshape.hpp"



CompositeShape::CompositeShape ( std::string name ) :
	Shape(name)
{}

/* virtual */
CompositeShape::~CompositeShape ()
{}

bool
CompositeShape::hit ( const Ray& ray, interval_t& tmin, HitRecord& hitrec ) const
{
	bool is_hit;
	HitRecord tmprec(hitrec);
	
	
	// go through all shapes and check for hits
	for ( unsigned i=0; i < shapes_.size(); ++i )
	{
		if ( shapes_[i]->hit(ray, tmin, tmprec) )
		{
			tmin = tmprec.t;
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
