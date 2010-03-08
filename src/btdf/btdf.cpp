#include "btdf.hpp"



namespace {
	const rgb black(0.0,0.0,0.0);
}



BTDF::BTDF()
{}


BTDF::~BTDF() 
{}

/* virtual */ rgb
BTDF::f ( const HitRecord& hitrec, const Vector& wo, const Vector& wi ) const
{
	return black;
}

/* virtual */ rgb
BTDF::sample_f ( const HitRecord& hitrec, const Vector& wo, Vector& wi ) const
{
	return black;
}

/* virtual */ rgb
BTDF::rho ( const HitRecord& hitrec, const Vector& wo ) const
{
	return black;
}

/* virtual */ bool
BTDF::tir ( const HitRecord& hitrec ) const
{
	return true;
}
