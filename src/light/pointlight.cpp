#include "pointlight.hpp"

// system header
#include <string>
#include <limits>

// projet header
#include <rgb.hpp>
#include <vector.hpp>
#include <hitrecord.hpp>
#include <scene.hpp>



PointLight::PointLight ( std::string name ) :
	Light     (name),
	ls_       (0.0),
	color_    (1.0,1.0,1.0),
	position_ ()
{}

PointLight::PointLight ( std::string name, float ls, rgb color, Point position ) :
	Light     (name),
	ls_       (ls),
	color_    (color),
	position_ (position)
{}

PointLight::~PointLight()
{}

Vector
PointLight::get_direction ( HitRecord& hitrec ) const
{
	return unify( position_ - hitrec.hitpoint );
}

rgb
PointLight::L ( HitRecord& hitrec ) const
{
	return ls_ * color_;
}

bool 
PointLight::in_shadow ( const Ray& s_ray, const HitRecord& hitrec ) const
{
	float t = 0;
	float d = (s_ray.origin() - position_).length();
	
	std::size_t count_obj = hitrec.scene_ptr->shapes.size();
	
	// go through all shapes and check for hits
	for ( unsigned i=0; i < count_obj; ++i )
	{
		if ( hitrec.scene_ptr->shapes[i]->hit(s_ray, t) and t < d )
		{
			return true;
		}
	}
	
	return false;
}

Point
PointLight::position () const
{
	return position_;
}