#include "pointlight.hpp"

// system header
#include <string>
#include <limits>

// projet header
#include <rgb.hpp>
#include <vector.hpp>
#include <hitrecord.hpp>
#include <scene.hpp>



PointLight::PointLight ( std::string name ) :
	Light     (name),
	ls_       (0.0),
	color_    (1.0,1.0,1.0),
	position_ ()
{}

PointLight::PointLight ( std::string name, Point position, rgb ls ) :
	Light     (name),
	ls_       (1.0),
	color_    (ls),
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
	return ls_ * color_;
}

bool 
PointLight::in_shadow ( const Ray& s_ray, const HitRecord& hitrec ) const
{
	float t = 0;
	float d = (s_ray.origin() - position_).length();
	
	Scene::shape_container_t::iterator it;
	
	// go through all shapes and check for hits
	for ( it = hitrec.scene_ptr->shapes.begin(); it != hitrec.scene_ptr->shapes.end(); ++it )
		if ( it->second->hit(s_ray, t) and t < d )
			return true;
	
	return false;
}

Point
PointLight::position () const
{
	return position_;
}