#include "raycast.hpp"

// project header
#include <tracer.hpp>
#include <hitrecord.hpp>

namespace {
	const float floatmax = std::numeric_limits<float>::max();
}



RayCast::RayCast ( Scene* scene_ptr ) :
	Tracer(scene_ptr)
{}

RayCast::~RayCast ()
{}

rgb
RayCast::trace ( const Ray& ray ) const
{
	HitRecord rec(scene_ptr_);
	float tmax = floatmax;
	float tmin = 0.0;
	
	if ( scene_ptr_->shapes.hit(ray,tmin,rec) )
	{
		rec.ray = ray;
		return rec.material_ptr->shade(rec);
	}
	
	return scene_ptr_->bgcolor;
}