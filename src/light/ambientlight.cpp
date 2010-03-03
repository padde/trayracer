#include "ambientlight.hpp"

// system header
#include <string>

// projet header
#include <rgb.hpp>
#include <vector.hpp>
#include <hitrecord.hpp>
#include <light.hpp>



AmbientLight::AmbientLight ( std::string name ) :
	Light  (name),
	ls_    (1.0),
	color_ (1.0,1.0,1.0)
{}

AmbientLight::AmbientLight ( std::string name, float ls, rgb color ) :
	Light  (name),
	ls_    (ls),
	color_ (color)
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
	return ls_ * color_;
}