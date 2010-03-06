#include "whitted.hpp"



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
	if ( depth > 3 )
		return black;
	else
	{
		HitRecord rec(scene_ptr_);
		float tmin = floatmax;

		if ( scene_ptr_->shapes.hit(ray,tmin,rec) )
		{
			rec.depth = depth;
			rec.ray   = ray;
			return rec.material_ptr->shade(rec);
		}
	}
	
	return scene_ptr_->bgcolor;
}