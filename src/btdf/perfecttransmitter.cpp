#include "perfecttransmitter.hpp"


// system header
#include <cmath>



namespace { const rgb black(0.0,0.0,0.0); }



PerfectTransmitter::PerfectTransmitter ( const float kt, const float ior ) :
	kt_ (kt),
	ior_(ior)
{}

PerfectTransmitter::~PerfectTransmitter ()
{}

/* virtual */ rgb 
PerfectTransmitter::sample_f ( const HitRecord& hitrec, const Vector& wo, Vector& wt ) const
{
	Vector n = hitrec.normal;
	float cos_theta_i = dot (n, wo);
	float eta = ior_;
	
	if ( cos_theta_i < 0.0 )
	{
		cos_theta_i = - cos_theta_i;
		n = -n;
		eta = 1.0 / eta;
	}
	
	float tmp = fabs( 1.0 - ( 1.0 - cos_theta_i * cos_theta_i ) / ( eta * eta ) );
	float cos_theta_2 = sqrt(tmp);
	wt = -wo / eta - ( cos_theta_2 - cos_theta_i / eta ) * n;
	
	rgb result = kt_ / ( eta * eta ) * rgb(1,1,1) / fabs(dot(n, wt));
	
	return result; 
}

/* virtual */ bool
PerfectTransmitter::tir ( const HitRecord& hitrec ) const
{
	Vector n  = hitrec.normal;
	Vector wo = - hitrec.ray.dir();
	float cos_theta_i = dot (n, wo);
	float eta = ior_;
	
	if ( cos_theta_i < 0.0 )
	{
		eta = 1.0 / eta;
	}
	
	return 1.0 - ( 1.0 - cos_theta_i * cos_theta_i ) / ( eta * eta ) < 0.0;
}
