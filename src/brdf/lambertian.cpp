#include "lambertian.hpp"

// system header

// project header



namespace {
	const float inv_pi = 0.3183098862;
}



Lambertian::Lambertian () :
	kd_(0.0),
	cd_(rgb(0.0, 0.0, 0.0))
{}

Lambertian::Lambertian ( const float& kd, const rgb& cd ) :
	kd_(kd),
	cd_(cd)
{}

Lambertian::~Lambertian()
{}

rgb
Lambertian::f ( const HitRecord& sr, const Vector& wo, const Vector& wi ) const
{
	return kd_ * cd_ * inv_pi;
}

rgb
Lambertian::rho ( const HitRecord& sr, const Vector& wo ) const
{
	return kd_ * cd_;
}

void
Lambertian::ka ( const float ka )
{
	kd_ = ka;
}

void
Lambertian::kd ( const float kd )
{
	kd_ = kd;
}

void
Lambertian::cd ( const rgb& cd )
{
	cd_ = cd;
}

float
Lambertian::ka () const
{
	return kd_;
}

float
Lambertian::kd () const
{
	return kd_;
}

rgb
Lambertian::cd () const
{
	return cd_;
}


