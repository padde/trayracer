#include "perfectspecular.hpp"

// system header
#include <cmath>



PerfectSpecular::PerfectSpecular ( const rgb& kr ) :
	kr_(kr)
{}

PerfectSpecular::~PerfectSpecular ()
{}

rgb
PerfectSpecular::sample_f ( const HitRecord& hitrec, const Vector& wo, Vector& wi ) const
{
	wi = -wo + 2.0 * hitrec.normal * dot(hitrec.normal, wo);
	rgb result = kr_ / fabs(dot(hitrec.normal, wi));
	
	return result;
}
