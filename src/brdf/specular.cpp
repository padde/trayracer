#include "specular.hpp"

// project header
#include <brdf.hpp>

// system header
#include <cmath>



Specular::Specular ( const rgb& ks, const float& exp ) :
	ks_(ks),
	exp_(exp)
{}

Specular::~Specular()
{}

rgb
Specular::f ( const HitRecord& hitrec, const Vector& wo, const Vector& wi ) const
{
	rgb L;
	
	// reflection direction
	Vector r = -wi + 2.0 * hitrec.normal * dot(hitrec.normal, wi);
	float rdotwo = dot(r, wo);
	
	// reflection detected
	if ( rdotwo > 0.0 )
		L = ks_ * pow(rdotwo, exp_);
	
	return L;
}
