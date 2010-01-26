// i/f header
#include "sphere.hpp"

// system header
#include <cmath>
#include <iostream>

// project header
#include <point.hpp>
#include <rgb.hpp>
#include <ray.hpp>
#include <shape.hpp>


Sphere::Sphere () :
	center_(0,0,0), radius_(0)
{}

Sphere::Sphere ( const Point& center, const float& radius ) :
	center_(center), radius_(radius)
{}

Sphere::~Sphere ()
{}

bool Sphere::hit ( const Ray& ray, interval_t tmin, interval_t tmax, HitRecord& hitrec ) const
{
	Vector tmp =  ray.origin() - center_;
	
	double a = dot( ray.dir(), ray.dir() );
	double b = dot( ray.dir(), tmp ) * 2;
	double c = dot( tmp, tmp ) - pow( radius_, 2);
	
	double discriminant = pow(b,2) - 4*a*c;
	
	if ( discriminant > 0 )
	{
		discriminant = sqrt(discriminant);
		double t = ( -b - discriminant ) / ( 2*a );
		
		if ( t < tmin )
			t = ( -b + discriminant ) / ( 2*a );
		
		if ( t < tmin or t > tmax ) {
			return false;
		}
		
		// hit detected
		hitrec.t = t;
		hitrec.hit = true;
		hitrec.normal = unify( ray.origin() + t*ray.dir() - center_ );
		hitrec.color = rgb(1,0,0);
		
		return true;
	}

	return false;
}

bool
Sphere::shadow_hit ( const Ray& ray, interval_t tmin, interval_t tmax ) const
{
	Vector tmp =  ray.origin() - center_;
	
	double a = dot( ray.dir(), ray.dir() );
	double b = dot( ray.dir(), tmp ) * 2;
	double c = dot( tmp, tmp ) - pow( radius_, 2);
	
	double discriminant = pow(b,2) - 4*a*c;
	
	if ( discriminant > 0 )
	{
		discriminant = sqrt(discriminant);
		double t = ( -b - discriminant ) / ( 2*a );
		
		if ( t < tmin )
			t = ( -b + discriminant ) / ( 2*a );
		
		if ( t < tmin or t > tmax ) {
			return false;
		}
		
		// hit detected
		return true;
	}
	
	return false;
}
