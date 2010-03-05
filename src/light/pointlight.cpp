#include "pointlight.hpp"

// system header
#include <string>
#include <limits>

// projet header
#include <rgb.hpp>
#include <vector.hpp>
#include <hitrecord.hpp>
#include <scene.hpp>



namespace {
	const float floatmax = std::numeric_limits<float>::max();
}



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
PointLight::in_shadow ( const Ray& ray, const HitRecord& hitrec ) const
{
	return ( hitrec.scene_ptr->shapes.hit(ray, 0, floatmax) );
}

Point
PointLight::position () const
{
	return position_;
}