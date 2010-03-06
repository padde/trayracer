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
PerfectSpecular::f ( const HitRecord& hitrec, const Vector& wo, Vector& wi ) const
{
	wi = -wo + 2.0 * hitrec.normal * dot(hitrec.normal, wo);
	
	return kr_ * cr_ / dot(hitrec.normal, wi);
}

rgb
PerfectSpecular::rho ( const HitRecord& hitrec, const Vector& wo ) const
{
	return black;
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