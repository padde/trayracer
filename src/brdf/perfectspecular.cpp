#include "perfectspecular.hpp"



namespace {
	const rgb black(0.0,0.0,0.0);
}



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
	
	return kr_ * cr_ / dot(hitrec.normal, wi);
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