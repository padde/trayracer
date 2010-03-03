#include "hitrecord.hpp"

// system header
#include <limits>



namespace {
	const double floatmax = std::numeric_limits<float>::max();
}

HitRecord::HitRecord ( Scene* ptr ) :
	hit          (false),
	t            (floatmax),
	color        (0.0,0.0,0.0),
	material_ptr (NULL),
	scene_ptr    (ptr)
{}

HitRecord::~HitRecord ()
{}

HitRecord&
HitRecord::operator= ( HitRecord const& rhs )
{
	hit           = rhs.hit;
	t             = rhs.t;
	color         = rhs.color;
	normal        = rhs.normal;
	material_ptr  = rhs.material_ptr;
	hitpoint      = rhs.hitpoint;
	scene_ptr     = rhs.scene_ptr;
	ray           = rhs.ray;
	
	return *this;
}