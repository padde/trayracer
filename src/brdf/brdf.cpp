#include "brdf.hpp"



namespace { const rgb black(0.0,0.0,0.0); }



BRDF::BRDF()
{}

BRDF::~BRDF() 
{}

/* virtual */ rgb 
BRDF::f ( const HitRecord& hitrec, const Vector& wo, const Vector& wi ) const
{
  return black;  
}

/* virtual */ rgb 
BRDF::sample_f ( const HitRecord& hitrec, const Vector& wo, Vector& wi ) const
{
  return black;  
}

/* virtual */ rgb 
BRDF::rho(const HitRecord& hitrec, const Vector& wo) const
{
  return black ; 
}
