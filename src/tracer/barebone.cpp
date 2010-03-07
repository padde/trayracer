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
	float tmin = floatmax;

	Scene::shape_container_t::iterator it;
	
	// go through all shapes and check for hits
	for ( it = scene_ptr_->shapes.begin(); it != scene_ptr_->shapes.end(); ++it )
	{
		if ( it->second->hit(ray,tmin,rec) )
		{
			return rgb(1,1,1);
		}
	}
	
	return scene_ptr_->bgcolor;
}