#include "lambertian.hpp"



namespace { const float inv_pi = 0.3183098862; }



Lambertian::Lambertian ( const rgb& kd ) :
	kd_(kd)
{}

Lambertian::~Lambertian()
{}

rgb
Lambertian::f ( const HitRecord& hitrec, const Vector& wo, const Vector& wi ) const
{
	return kd_ * inv_pi;
}

rgb
Lambertian::rho ( const HitRecord& hitrec, const Vector& wo ) const
{
	return kd_;
}
