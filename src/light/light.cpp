#include "light.hpp"

// system header
#include <string>



Light::Light ( std::string name ) :
	name_(name)
{}

Light::~Light()
{}

/* virtual */ bool
Light::in_shadow ( const Ray& ray, const HitRecord& hitrec ) const
{
	return false;
}

/* virtual */ Point
Light::position () const
{
	return Point(0,0,0);
}