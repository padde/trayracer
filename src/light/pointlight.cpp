#include "pointlight.hpp"

// projet header
#include <scene.hpp>



PointLight::PointLight ( std::string name, Point position, rgb ls ) :
	Light     (name),
	ls_       (ls),
	position_ (position)
{}

PointLight::~PointLight()
{}

Vector
PointLight::get_direction ( HitRecord& hitrec ) const
{
	return unify( position_ - hitrec.hitpoint );
}

rgb
PointLight::L ( HitRecord& hitrec ) const
{
	return ls_;
}

bool 
PointLight::in_shadow ( const Ray& s_ray, const HitRecord& hitrec ) const
{
	float tmin = 0;
	float d = (s_ray.origin() - position_).length();
	
	Scene::shape_container_t::iterator it;
	
	// go through all shapes and check for hits
	for ( it = hitrec.scene_ptr->shapes.begin(); it != hitrec.scene_ptr->shapes.end(); ++it )
		if ( it->second->hit(s_ray, tmin) and tmin < d )
			return true;
	
	return false;
}

Point
PointLight::position () const
{
	return position_;
}