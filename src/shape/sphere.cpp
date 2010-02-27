// i/f header
#include "sphere.hpp"

// system header
#include <cmath>
#include <iostream>

// project header
#include <point.hpp>
#include <vector.hpp>
#include <matrix.hpp>
#include <rgb.hpp>
#include <ray.hpp>
#include <shape.hpp>

using namespace std;

Sphere::Sphere () :
	radius_(0)
{}

Sphere::Sphere ( const float& radius ) :
	radius_(radius)
{}

Sphere::~Sphere ()
{}

bool Sphere::hit ( const Ray& original_ray, interval_t tmin, interval_t tmax, HitRecord& hitrec ) const
{
	// transform ray to object space
	Ray ray = original_ray.transform(trans_);
	
	// some helper variables
	Vector org = ray.origin();
	Vector dir = ray.dir();
	float a = dot(dir, dir);
	float b = dot(dir, org) * 2;
	float c = dot(org, org) - pow(radius_, 2);
	float discriminant = pow(b,2) - 4*a*c;
	
	if ( discriminant > 0 )
	{
		discriminant = sqrt(discriminant);
		double t = ( -b - discriminant ) / ( 2*a );
		
		if ( t < tmin )
			t = ( -b + discriminant ) / ( 2*a );
		
		if ( t < tmin or t > tmax )
			return false;
		
		// hit detected
		hitrec.t      = t;
		hitrec.hit    = true;
		hitrec.normal = unify( ray.origin() + t*ray.dir());
		hitrec.color  = rgb(0,1,0);
		
		return true;
	}
	
	return false;
}

bool
Sphere::hit ( const Ray& ray, interval_t tmin, interval_t tmax ) const
{
	/*Vector tmp =  ray.origin() - center_;
	
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
	
	return false;*/
}
