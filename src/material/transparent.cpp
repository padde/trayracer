#include "transparent.hpp"



// system header
#include <cmath>
#include <iostream>

// project header
#include <scene.hpp>



Transparent::Transparent ( std::string name, const rgb ka, const rgb kd, const rgb ks, const float exp, const rgb kr, const float kt, const float ior ) :
	Phong( name, ka, kd, ks, exp ),
	reflective_brdf_ptr_(NULL),
	specular_btdf_ptr_(NULL)
{
	reflective_brdf_ptr_ = new PerfectSpecular( 1.0, kr );
	specular_btdf_ptr_   = new PerfectTransmitter( kt, ior );
}
	

Transparent::~Transparent()
{
	delete reflective_brdf_ptr_;
	delete specular_btdf_ptr_;
}

/* virtual */ rgb
Transparent::shade ( HitRecord& hitrec ) const
{
	rgb L = Phong::shade(hitrec);
	
	Vector n  = hitrec.normal;
	Vector wo = - hitrec.ray.dir();
	wo.unify();
	Vector wi;
	rgb fr = reflective_brdf_ptr_->sample_f(hitrec,wo,wi);
	Ray reflected_ray( hitrec.hitpoint, wi );
	
	if ( specular_btdf_ptr_->tir(hitrec) )
	{
		L += hitrec.scene_ptr->tracer_ptr->trace( reflected_ray, hitrec.depth + 1 );
	}
	else
	{
		Vector wt;
		rgb ft = specular_btdf_ptr_->sample_f(hitrec,wo,wt);
		Ray transmitted_ray(hitrec.hitpoint,wt);
		
		L += fr * ( hitrec.scene_ptr->tracer_ptr->trace(reflected_ray,   hitrec.depth + 1) ) * fabs( dot(n,wi) );
		L += ft * ( hitrec.scene_ptr->tracer_ptr->trace(transmitted_ray, hitrec.depth + 1) ) * fabs( dot(n,wt) );
	}
	
	return L;
}