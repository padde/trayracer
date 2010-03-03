#include "matte.hpp"

// system header
#include <string>

// project header
#include <rgb.hpp>
#include <hitrecord.hpp>
#include <material.hpp>
#include <scene.hpp>
#include <ambientlight.hpp>


Matte::Matte ( std::string name, const float ka, const float kd, const rgb cd ) :
	Material (name)
{
	ambient_brdf_ptr_ = new Lambertian(ka,cd);
	diffuse_brdf_ptr_ = new Lambertian(kd,cd);
}

Matte::~Matte()
{
	delete ambient_brdf_ptr_;
	delete diffuse_brdf_ptr_;
}

rgb
Matte::shade ( HitRecord& hitrec ) const
{
	Vector wo = - hitrec.ray.dir();
	
	rgb L = ambient_brdf_ptr_->rho(hitrec,wo) *
		hitrec.scene_ptr->ambient_ptr->L(hitrec);
	
	int num_lights = hitrec.scene_ptr->lights.size();
	
	for (int i = 0; i < num_lights; ++i)
	{
		Vector wi     = hitrec.scene_ptr->lights[i]->get_direction(hitrec);
		float  ndotwi = dot(hitrec.normal, wi);
		
		if (ndotwi > 0.0)
			L += diffuse_brdf_ptr_->f(hitrec, wo, wi) *
				hitrec.scene_ptr->lights[i]->L(hitrec) * ndotwi;
	}
	
	return L;
}