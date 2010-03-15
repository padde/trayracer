#include "sphere.hpp"

// system header
#include <cmath>

// project header
#include <box.hpp>

namespace { const double epsilon = 0.01; }



Sphere::Sphere ( std::string name, const Point& center, const float& radius, Material* material ) :
	Shape( name, material ),
	radius_(radius), center_(center)
{
	bbox_.first  = center_ - Vector(radius_,radius_,radius_);
	bbox_.second = center_ + Vector(radius_,radius_,radius_);
}

Sphere::~Sphere ()
{}

bool Sphere::hit ( const Ray& original_ray, interval_t& tmin, HitRecord& hitrec ) const
{
	// transform ray to object space
	Ray ray = original_ray.transform(inv_trans_);
	
	// some helper variables
	Vector org = ray.origin() - center_;
	Vector dir = ray.dir();
	float a = dot(dir, dir);
	float b = dot(dir, org) * 2.0;
	float c = dot(org, org) - radius_ * radius_;
	float discriminant = b * b - 4.0 * a * c;
	
	if ( discriminant > 0.0 )
	{
		discriminant = sqrt(discriminant);
		double t = ( -b - discriminant ) / ( 2.0*a );
		
		if ( t > epsilon and t < tmin )
		{
			// hit detected
			tmin = t;
			
			hitrec.t            = t;
			hitrec.hit          = true;
			hitrec.material_ptr = material_ptr_;
			hitrec.hitpoint     = (back_trans_ * ray.origin()) + t * (back_trans_ * ray.dir());
			hitrec.ray          = original_ray;
			hitrec.normal       = unify(hitrec.hitpoint - back_trans_ * center_);
			
			return true;
		}
		
		t = ( -b + discriminant ) / ( 2.0*a );
		
		if ( t > epsilon and t < tmin )
		{
			// hit detected
			tmin = t;
			
			hitrec.t            = t;
			hitrec.hit          = true;
			hitrec.material_ptr = material_ptr_;
			hitrec.hitpoint     = (back_trans_ * ray.origin()) + t * (back_trans_ * ray.dir());
			hitrec.ray          = original_ray;
			hitrec.normal       = unify(hitrec.hitpoint - back_trans_ * center_);
			
			return true;
		}
	}
	
	return false;
}

bool
Sphere::hit ( const Ray& original_ray, interval_t& tmin ) const
{
	// transform ray to object space
	Ray ray = original_ray.transform(inv_trans_);
	
	// some helper variables
	Vector org = ray.origin() - center_;
	Vector dir = ray.dir();
	float a = dot(dir, dir);
	float b = dot(dir, org) * 2;
	float c = dot(org, org) - pow(radius_, 2);
	float discriminant = pow(b,2) - 4*a*c;
	
	if ( discriminant > 0 )
	{
		discriminant = sqrt(discriminant);
		double t = ( -b - discriminant ) / ( 2.0*a );
		
		if ( t > epsilon )
		{
			// hit detected
			tmin = t;
			return true;
		}
		
		t = ( -b + discriminant ) / ( 2.0*a );
		
		if ( t > epsilon )
		{
			// hit detected
			tmin = t;
			return true;
		}
	}
	
	return false;
}
