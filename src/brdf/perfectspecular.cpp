#include "perfectspecular.hpp"

#include <cmath>

PerfectSpecular::PerfectSpecular ( const float& kr, const rgb& cr ) :
	kr_(kr),
	cr_(cr)
{}

PerfectSpecular::~PerfectSpecular ()
{}

rgb
PerfectSpecular::sample_f ( const HitRecord& hitrec, const Vector& wo, Vector& wi ) const
{
	wi = -wo + 2.0 * hitrec.normal * dot(hitrec.normal, wo);
	rgb result = kr_ * cr_ / fabs(dot(hitrec.normal, wi));
	
	return result;
}

void
PerfectSpecular::kr ( const float kr )
{
	kr_ = kr;
}

void
PerfectSpecular::cr ( const rgb&  cr )
{
	cr_ = cr;
}

float
PerfectSpecular::kr () const
{
	return kr_;
}

rgb 
PerfectSpecular::cr () const
{
	return cr_;
}