#include "box.hpp"
#include <iostream>

namespace {
	const double epsilon = 0.05;
	const Vector normals[6] = {
		Vector(-1,  0,  0), 
		Vector( 0, -1,  0),
		Vector( 0,  0, -1),
		Vector( 1,  0,  0),
		Vector( 0,  1,  0),
		Vector( 0,  0,  1) };
}



Box::Box ( std::string name, const Point& a, const Point& b, Material* material ) :
	Shape( name, material ),
	a_(a), b_(b)
{
	if (a_[0] > b_[0])
		std::swap(a_[0], b_[0]);
	
	if (a_[1] > b_[1])
		std::swap(a_[1], b_[1]);
	
	if (a_[2] > b_[2])
		std::swap(a_[2], b_[2]);
		
	bbox_.first  = a_;
	bbox_.second = b_;
}

Box::~Box ()
{}

bool
Box::hit ( const Ray& original_ray, interval_t& tmin, HitRecord& hitrec ) const
{
	// transform ray to object space
	Ray ray = original_ray.transform(inv_trans_);
	
	double ox = ray.origin()[0];
	double oy = ray.origin()[1];
	double oz = ray.origin()[2];
	
	double dx = ray.dir()[0];
	double dy = ray.dir()[1];
	double dz = ray.dir()[2];
	
	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;
	
	double a = 1.0 / dx;
	if (a >= 0) {
		tx_min = (a_[0] - ox) * a;
		tx_max = (b_[0] - ox) * a;
	} else {
		tx_min = (b_[0] - ox) * a;
		tx_max = (a_[0] - ox) * a;
	}
	
	double b = 1.0 / dy;
	if (b >= 0) {
		ty_min = (a_[1] - oy) * b;
		ty_max = (b_[1] - oy) * b;
	} else {
		ty_min = (b_[1] - oy) * b;
		ty_max = (a_[1] - oy) * b;
	}
	
	if (tx_min > ty_max or ty_min > tx_max)
		return false;
	
	double c = 1.0 / dz;
	if (c >= 0) {
		tz_min = (a_[2] - oz) * c;
		tz_max = (b_[2] - oz) * c;
	} else {
		tz_min = (b_[2] - oz) * c;
		tz_max = (a_[2] - oz) * c;
	}
	
	double t0, t1;
	int face_in, face_out;
	
	if (tx_min > tz_max or tz_min > tx_max)
		return false;
	
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
	
	if (t0 < t1 and t1 > epsilon and t0 < tmin) {
		// hit detected
		
		if (t0 > epsilon) { // ray hits outside
			tmin = t0;
			hitrec.normal = unify(back_trans_ * normals[face_in]);
		} else {            // ray hits inside
			tmin = t1;
			hitrec.normal = unify(back_trans_ * normals[face_out]);
		}
		
		hitrec.t            = tmin;
		hitrec.hit          = true;
		hitrec.material_ptr = material_ptr_;
		hitrec.hitpoint     = (back_trans_ * ray.origin()) + tmin * ( back_trans_ * ray.dir());
		hitrec.ray          = original_ray;
		
		return true;
	}
	
	return false;
}

bool
Box::hit ( const Ray& original_ray, interval_t& tmin ) const
{
	// transform ray to object space
	Ray ray = original_ray.transform(inv_trans_);
	
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
	
	if (t0 < t1 and t1 > epsilon and t0 < tmin)
	{
		if (t0 > epsilon) {
			tmin = t0;
		} else {
			tmin = t1;
		}
		
		return true;
	}
	
	return false;
}

Point
Box::a () const
{
	return a_;
}

Point
Box::b () const
{
	return b_;
}

void
Box::transform ( const Matrix& new_trans )
{
	using namespace std;
	
	Shape::transform ( new_trans );
	
	Point p1 ( a_[0], a_[1], a_[2] );
	Point p2 ( a_[0], a_[1], b_[2] );
	Point p3 ( a_[0], b_[1], a_[2] );
	Point p4 ( a_[0], b_[1], b_[2] );
	Point p5 ( b_[0], a_[1], a_[2] );
	Point p6 ( b_[0], a_[1], b_[2] );
	Point p7 ( b_[0], b_[1], a_[2] );
	Point p8 ( b_[0], b_[1], b_[2] );
	
	p1 = trans_ * p1;
	p2 = trans_ * p2;
	p3 = trans_ * p3;
	p4 = trans_ * p4;
	p5 = trans_ * p5;
	p6 = trans_ * p6;
	p7 = trans_ * p7;
	p8 = trans_ * p8;
	
	float min_x = min(p1[0],min(p2[0],min(p3[0],min(p4[0],min(p5[0],min(p6[0],min(p7[0],p8[0])))))));
	float min_y = min(p1[1],min(p2[0],min(p3[0],min(p4[0],min(p5[0],min(p6[0],min(p7[0],p8[0])))))));
	float min_z = min(p1[2],min(p2[0],min(p3[0],min(p4[0],min(p5[0],min(p6[0],min(p7[0],p8[0])))))));
	float max_x = max(p1[0],max(p2[0],max(p3[0],max(p4[0],max(p5[0],max(p6[0],max(p7[0],p8[0])))))));
	float max_y = max(p1[1],max(p2[0],max(p3[0],max(p4[0],max(p5[0],max(p6[0],max(p7[0],p8[0])))))));
	float max_z = max(p1[2],max(p2[0],max(p3[0],max(p4[0],max(p5[0],max(p6[0],max(p7[0],p8[0])))))));
	
	bbox_.first  = Point(min_x,min_y,min_z);
	bbox_.second = Point(max_x,max_y,max_z);
}

