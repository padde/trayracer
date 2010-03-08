#include "phong.hpp"

// system header
#include <string>

// project header
#include <rgb.hpp>
#include <hitrecord.hpp>
#include <material.hpp>
#include <scene.hpp>



Phong::Phong ( std::string name, const rgb ka, const rgb kd, const rgb ks, const float ex ) :
	Material (name)
{
	ambient_brdf_ptr_  = new Lambertian(1.0,ka);
	diffuse_brdf_ptr_  = new Lambertian(1.0,kd);
	specular_brdf_ptr_ = new Specular(1.0,ks,ex);
}

Phong::~Phong()
{
	delete ambient_brdf_ptr_;
	delete diffuse_brdf_ptr_;
	delete specular_brdf_ptr_;
}

rgb
Phong::shade ( HitRecord& hitrec ) const
{
	Vector wo = - hitrec.ray.dir();
	
	rgb L = ambient_brdf_ptr_->rho(hitrec,wo) *
		hitrec.scene_ptr->ambient_ptr->L(hitrec);
	
	int num_lights = hitrec.scene_ptr->lights.size();
	
	for (int i = 0; i < num_lights; ++i)
	{
		Vector wi     = hitrec.scene_ptr->lights[i]->get_direction(hitrec);
		float  ndotwi = dot(hitrec.normal, wi);
		
		if ( ndotwi > 0.0 )
		{
			// shoot ray from hint point to light source
			Ray s_ray( hitrec.hitpoint, wi);
			
			// check if s_ray hits an object
			bool in_shadow = hitrec.scene_ptr->lights[i]->in_shadow(s_ray, hitrec);
			
			if ( ! in_shadow )
			{
				L += ( diffuse_brdf_ptr_->f (hitrec, wo, wi)  +
				       specular_brdf_ptr_->f(hitrec, wo, wi)
				     ) * hitrec.scene_ptr->lights[i]->L(hitrec) * ndotwi;
			}
		}
	}
	
	return L;
}