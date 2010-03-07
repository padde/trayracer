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
RayCast::trace ( const Ray& ray, int max_depth ) const
{
	HitRecord rec(scene_ptr_);
	float tmin = floatmax;
	
	Scene::shape_container_t::iterator it;
	
	// go through all shapes and check for hits
	for ( it = scene_ptr_->shapes.begin(); it != scene_ptr_->shapes.end(); ++it )
	{
		if ( it->second->hit(ray,tmin,rec) )
		{
			rec.ray = ray;
			return rec.material_ptr->shade(rec);
		}
	}
	
	return scene_ptr_->bgcolor;
}