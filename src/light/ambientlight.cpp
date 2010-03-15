#include "ambientlight.hpp"



AmbientLight::AmbientLight ( std::string name, rgb ls ) :
	Light  (name),
	ls_    (ls)
{}

AmbientLight::~AmbientLight ()
{}

Vector
AmbientLight::get_direction ( HitRecord& hitrec ) const
{
	return Vector(0.0,0.0,0.0);
}

rgb
AmbientLight::L ( HitRecord& hitrec ) const
{
	return ls_;
}