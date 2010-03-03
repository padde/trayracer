#include "pointlight.hpp"

// system header
#include <string>

// projet header
#include <rgb.hpp>
#include <vector.hpp>
#include <hitrecord.hpp>



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