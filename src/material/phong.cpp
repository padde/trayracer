#include "phong.hpp"

// system header
#include <string>

// project header
#include <rgb.hpp>
#include <hitrecord.hpp>
#include <material.hpp>
#include <scene.hpp>



Phong::Phong ( std::string name, const float ka, const float kd, const float ks, const float ex, const rgb c ) :
	Material (name)
{
	ambient_brdf_ptr_  = new Lambertian(ka,c);
	diffuse_brdf_ptr_  = new Lambertian(kd,c);
	specular_brdf_ptr_ = new Specular(ks,c,ex);
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
	wo.unify();
	
	rgb L = ambient_brdf_ptr_->rho(hitrec,wo) *
		hitrec.scene_ptr->ambient_ptr->L(hitrec);
	
	int num_lights = hitrec.scene_ptr->lights.size();
	
	for (int i = 0; i < num_lights; ++i)
	{
		Vector wi     = hitrec.scene_ptr->lights[i]->get_direction(hitrec);
		float  ndotwi = dot(hitrec.normal, wi);
		
		if ( ndotwi > 0.0 )
		{
			/*Ray sray(hitrec.hitpoint, hitrec.scene_ptr->lights[i]->position());
			if ( ! hitrec.scene_ptr->lights[i]->in_shadow(sray, hitrec) )
			{*/
				L += ( diffuse_brdf_ptr_->f (hitrec, wo, wi)  +
				       specular_brdf_ptr_->f(hitrec, wo, wi)
				     ) * hitrec.scene_ptr->lights[i]->L(hitrec) * ndotwi;
			/*}*/
		}
	}
	
	return L;
}