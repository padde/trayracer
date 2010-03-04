#include "specular.hpp"

// project header
#include <brdf.hpp>

// system header
#include <cmath>



namespace {
	const rgb black(0.0,0.0,0.0);
}



Specular::Specular () :
	ks_(0.0),
	exp_(0.0),
	cs_(1,1,1)
{}

Specular::Specular ( const float& ks, const rgb& cs, const float& exp ) :
	ks_(ks),
	exp_(exp),
	cs_(cs)
{}

Specular::~Specular()
{}

rgb
Specular::f ( const HitRecord& hitrec, const Vector& wo, const Vector& wi ) const
{
	rgb L;
	float ndotwi = dot(hitrec.normal, wi);
	
	Vector r = -wi + 2.0 * hitrec.normal * ndotwi;
	float rdottwo = dot(r, wo);
	
	if ( rdottwo > 0.0 )
		L = ks_ * cs_ * pow(rdottwo, exp_);
	
	return L;
}

rgb
Specular::rho ( const HitRecord& hitrec, const Vector& wo ) const
{
	return black;
}

void
Specular::ks  ( const float ks )
{
	ks_ = ks;
}

void
Specular::exp ( const float e )
{
	exp_ = e;
}

void
Specular::cs ( const rgb&  cs )
{
	cs_ = cs;
}
	
float
Specular::ks () const
{
	return ks_;
}

float
Specular::exp () const
{
	return exp_;
}

rgb
Specular::cs () const
{
	return cs_;
}