#include "tracer.hpp"

#include <iostream>


Tracer::Tracer ( Scene* scene_ptr ) :
	scene_ptr_(scene_ptr)
{}

/* virtual */
Tracer::~Tracer ()
{}

/* virtual */ rgb
Tracer::trace ( const Ray& ray ) const
{
	rgb result(0.1*1,0.1*1,0.1*1);
	return result;
}