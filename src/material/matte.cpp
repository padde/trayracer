#include "matte.hpp"

// project header
#include <scene.hpp>



Matte::Matte ( std::string name, const rgb ka, const rgb kd ) :
	Material (name)
{
	ambient_brdf_ptr_ = new Lambertian(ka);
	diffuse_brdf_ptr_ = new Lambertian(kd);
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
	
	rgb L = ambient_brdf_ptr_->rho(hitrec,wo) *    /* ambient part of material */
		hitrec.scene_ptr->ambient_ptr->L(hitrec);  /* ambient light in scene */
	
	int num_lights = hitrec.scene_ptr->lights.size();
	
	// for every light in scene
	for (int i = 0; i < num_lights; ++i)
	{
		// vector of incoming light
		Vector wi = hitrec.scene_ptr->lights[i]->get_direction(hitrec);
		
		// angle between normal and incoming light
		float ndotwi = dot(hitrec.normal, wi);
		
		// n, wi not perpendicular
		if ( ndotwi > 0.0 )
		{
			// shoot ray from hint point to light source
			Ray s_ray( hitrec.hitpoint, wi);
			
			// check if s_ray hits an object
			bool in_shadow = hitrec.scene_ptr->lights[i]->in_shadow(s_ray, hitrec);
			
			if ( ! in_shadow )
			{
				L += diffuse_brdf_ptr_->f(hitrec, wo, wi) *
				     hitrec.scene_ptr->lights[i]->L(hitrec) * ndotwi;
			}
		}
	}
	
	return L;
}