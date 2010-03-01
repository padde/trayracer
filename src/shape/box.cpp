// i/f header
#include "box.hpp"

// system header
#include <iostream>
#include <limits>

// project header
#include <shape.hpp>

namespace {
	// internal stuff
	
	const double epsilon = std::numeric_limits<double>::epsilon() * 96;
	
	const Vector normals[6] = {
		Vector(-1, 0, 0), 
		Vector(0, -1, 0),
		Vector(0, 0, -1),
		Vector(1, 0, 0),
		Vector(0, 1, 0),
		Vector(0, 0, 1) };
}


Box::Box ()
{}

Box::Box ( const Point& a, const Point& b ) :
	a_(a), b_(b)
{
	if (a_[0] > b_[0])
		std::swap(a_[0], b_[0]);
	
	if (a_[1] > b_[1])
		std::swap(a_[1], b_[1]);
	
	if (a_[2] > b_[2])
		std::swap(a_[2], b_[2]);
}

Box::~Box ()
{}

bool
Box::hit ( const Ray& original_ray, interval_t tmin, interval_t tmax, HitRecord& hitrec ) const
{
	// transform ray to object space
	Ray ray = original_ray.transform(trans_);
	
	Point p1(a_), p2(b_);
	
	double ox = ray.origin()[0];
	double oy = ray.origin()[1];
	double oz = ray.origin()[2];
	double dx = ray.dir()[0];
	double dy = ray.dir()[1];
	double dz = ray.dir()[2];
	double t0, t1;
	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;
	int face_in, face_out;
	
	double a = 1.0 / dx;
	if (a >= 0) {
		tx_min = (p1[0] - ox) * a;
		tx_max = (p2[0] - ox) * a;
	} else {
		tx_min = (p2[0] - ox) * a;
		tx_max = (p1[0] - ox) * a;
	}
	
	double b = 1.0 / dy;
	if (b >= 0) {
		ty_min = (p1[1] - oy) * b;
		ty_max = (p2[1] - oy) * b;
	} else {
		ty_min = (p2[1] - oy) * b;
		ty_max = (p1[1] - oy) * b;
	}
	
	if (tx_min > ty_max or ty_min > tx_max)
		return false;
	
	double c = 1.0 / dz;
	if (c >= 0) {
		tz_min = (p1[2] - oz) * c;
		tz_max = (p2[2] - oz) * c;
	} else {
		tz_min = (p2[2] - oz) * c;
		tz_max = (p1[2] - oz) * c;
	}
	
	if (tx_min > tz_max or tz_min > tx_max)
		return false;
		
	// find largest entering t value
	if (tx_min > ty_min) {
		t0 = tx_min;
		face_in = (a >= 0.0) ? 0 : 3; 
	} else {
		t0 = ty_min;
		face_in = (b >= 0.0) ? 1 : 4;
	}
	
	if (tz_min > t0) {
		t0 = tz_min;
		face_in = (c >= 0.0) ? 2 : 5;
	}
	
	// find smallest exiting t value
	if (tx_max < ty_max) {
	  t1 = tx_max;
	  face_out = (a >= 0.0) ? 3 : 0;
	} else {
	  t1 = ty_max;
	  face_out = (b >= 0.0) ? 4 : 1;
	}
	
	if (tz_max < t1) {
	  t1 = tz_max;
	  face_out = (c >= 0.0) ? 5 : 2;
	}
	
	
	// if (t1 > epsilon and t1 < tmax) {
	if (t0 < t1 and t1 > epsilon and t0 > tmin and t0 < tmax) {
		// hit detected
		
		if (t0 > epsilon) { // ray hits outside
			tmin = t0;
			hitrec.normal = normals[face_in];   
		} else {
			tmin = t1;
			hitrec.normal = normals[face_out]; 
		}
		hitrec.t      = tmin;
		hitrec.hit    = true;
		hitrec.color  = rgb(1,0,0);
		return true;
	}
	
	// if ( t >= tmin and t <= tmax )
	// {
	// 	// hit detected
	// 	hitrec.t      = t;
	// 	hitrec.hit    = true;
	// 	hitrec.normal = unify( t*ray.dir() + org );
	// 	hitrec.color  = rgb(1,1,0);
	// 	return true;
	// }
	
	return false;
}

bool
Box::hit ( const Ray& ray, interval_t tmin, interval_t tmax ) const
{
	return false;
}
