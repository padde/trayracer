#include "whitted.hpp"

// system header
#include <limits>

namespace {
	const rgb black(0.0,0.0,0.0);
	const float floatmax = std::numeric_limits<float>::max();
}



Whitted::Whitted ( Scene* scene_ptr ) :
	Tracer(scene_ptr)
{}

Whitted::~Whitted ()
{}

rgb
Whitted::trace ( const Ray& ray, int depth ) const
{
	if ( depth > 4 )
		return black;
	else
	{
		HitRecord rec(scene_ptr_);
		float tmin = floatmax;
		bool is_hit = false;
		
		Scene::shape_container_t::const_iterator it;
		
		// go through all shapes and check for hits
		for ( it = scene_ptr_->shapes.begin(); it != scene_ptr_->shapes.end(); ++it )
			if ( it->second->hit(ray,tmin,rec) ) {
				rec.depth = depth;
				is_hit = true;
			}
			
		if (is_hit)
			return rec.material_ptr->shade(rec).max_to_one();
	}
	
	return scene_ptr_->bgcolor;
}