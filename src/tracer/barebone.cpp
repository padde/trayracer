#include "barebone.hpp"

namespace {
	const float floatmax = std::numeric_limits<float>::max();
}



BareBone::BareBone ( Scene* scene_ptr ):
	Tracer(scene_ptr)
{}

BareBone::~BareBone ()
{}

rgb
BareBone::trace ( const Ray& ray, int max_depth ) const
{
	HitRecord rec(scene_ptr_);
	float tmax = floatmax;
	float tmin = 0.0;
	
	if ( scene_ptr_->shapes.hit(ray,tmin,rec) )
		return rgb(1,1,1);
	
	return scene_ptr_->bgcolor;
}