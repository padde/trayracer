#include "reflective.hpp"

// system header
#include <string>

// project header
#include <rgb.hpp>
#include <hitrecord.hpp>
#include <scene.hpp>
#include <phong.hpp>



Reflective::Reflective ( std::string name, const rgb ka, const rgb kd, const rgb ks, const float exp, const rgb kr ) :
	Phong( name, ka, kd, ks, exp ),
	reflective_brdf_ptr_(NULL)
{
	reflective_brdf_ptr_ = new PerfectSpecular( 1.0, kr );
}

Reflective::~Reflective()
{
	delete reflective_brdf_ptr_;
}

/* virtual */ rgb
Reflective::shade ( HitRecord& hitrec ) const
{
	rgb L = Phong::shade(hitrec);
	
	Vector wi;
	Vector wo = - hitrec.ray.dir();
	
	rgb fr = reflective_brdf_ptr_->sample_f(hitrec,wo,wi);
	
	Ray r_ray( hitrec.hitpoint, wi);
	float ndotwi = dot(hitrec.normal, wi);

	L += fr * ( hitrec.scene_ptr->tracer_ptr->trace(r_ray, hitrec.depth + 1) ) * ndotwi;
	
	return L;
}