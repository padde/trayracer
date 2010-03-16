#include "reflective.hpp"

// project header
#include <scene.hpp>
#include <cmath>
#include <iostream>



Reflective::Reflective ( std::string name, const rgb ka, const rgb kd, const rgb ks, const float exp, const rgb kr ) :
	Phong( name, ka, kd, ks, exp ),
	reflective_brdf_ptr_(NULL)
{
	reflective_brdf_ptr_ = new PerfectSpecular(kr);
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
	
	/*if ( L[rgb::r]<0 or L[rgb::g]<0 or L[rgb::b]<0 )
	{
		std::cout << "--------------------------------------------"<< std::endl;
		std::cout << "normal = " << hitrec.normal << std::endl;
		std::cout << "wi     = " << wi << std::endl;
		std::cout << "|wi|   = " << wi.length() << std::endl;
		std::cout << "wo     = " << wo << std::endl;
		std::cout << "|wo|   = " << wo.length() << std::endl;
		std::cout << "L      = " << fr * ( hitrec.scene_ptr->tracer_ptr->trace(r_ray, hitrec.depth + 1) ) * ndotwi << std::endl;
	}*/
	
	return L;
}

