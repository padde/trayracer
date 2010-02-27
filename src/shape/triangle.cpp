// i/f header
#include "triangle.hpp"

// system header
#include <cmath>
#include <iostream>

// project header
#include <point.hpp>
#include <vector.hpp>
#include <rgb.hpp>
#include <ray.hpp>
#include <shape.hpp>



Triangle::Triangle () :
	a_(0,0,0), b_(0,0,0), c_(0,0,0)
{}

Triangle::Triangle ( const Point& a, const Point& b, const Point& c ) :
	a_(a), b_(b), c_(c)
{}

Triangle::~Triangle ()
{}

bool Triangle::hit ( const Ray& ray, interval_t tmin, interval_t tmax, HitRecord& hitrec ) const
{
	float A = a_[0] - b_[0];
	float B = a_[1] - b_[1];
	float C = a_[2] - b_[2];
	
	float D = a_[0] - c_[0];
	float E = a_[1] - c_[1];
	float F = a_[2] - c_[2];
	
	float G = ray.dir()[0];
	float H = ray.dir()[1];
	float I = ray.dir()[2];
	
	float J = a_[0] - ray.origin()[0];
	float K = a_[1] - ray.origin()[1];
	float L = a_[2] - ray.origin()[2];
	
	float EIHF = E*I - H*F;
	float GFDI = G*F - D*I;
	float DHEG = D*H - E*G;
	
	float denom = A*EIHF + B*GFDI + C*DHEG;
	
	float beta = ( J*EIHF + K*GFDI + L*DHEG ) / denom;
	
	if ( beta <= 0.0f or beta >= 1.0f )
		return false;
	
	float AKJB = A*K - J*B;
	float JCAL = J*C - A*L;
	float BLKC = B*L - K*C;
	
	float gamma = ( I*AKJB + H*JCAL + G*BLKC ) / denom;
	
	if ( gamma <= 0.0f or beta + gamma >= 1.0f )
		return false;
	
	float t = -( F*AKJB + E*JCAL + D*BLKC ) / denom;
	
	if ( t >= tmin and t <= tmax )
	{
		// hit detected
		hitrec.t = t;
		hitrec.hit = true;
		hitrec.normal = unify( cross( Vector(b_ - a_), Vector(c_ - a_) ) );
		hitrec.color = rgb(1,0,0);
		
		return true;
	}
	
	return false;
}

bool Triangle::hit ( const Ray& ray, interval_t tmin, interval_t tmax ) const
{
	float A = a_[0] - b_[0];
	float B = a_[1] - b_[1];
	float C = a_[2] - b_[2];
	
	float D = a_[0] - c_[0];
	float E = a_[1] - c_[1];
	float F = a_[2] - c_[2];
	
	float G = ray.dir()[0];
	float H = ray.dir()[1];
	float I = ray.dir()[2];
	
	float J = a_[0] - ray.origin()[0];
	float K = a_[1] - ray.origin()[1];
	float L = a_[2] - ray.origin()[2];
	
	float EIHF = E*I - H*F;
	float GFDI = G*F - D*I;
	float DHEG = D*H - E*G;
	
	float denom = A*EIHF + B*GFDI + C*DHEG;
	
	float beta = ( J*EIHF + K*GFDI + L*DHEG ) / denom;
	
	if ( beta <= 0.0f or beta >= 1.0f )
		return false;
	
	float AKJB = A*K - J*B;
	float JCAL = J*C - A*L;
	float BLKC = B*L - K*C;
	
	float gamma = ( I*AKJB + H*JCAL + G*BLKC ) / denom;
	
	if ( gamma <= 0.0f or beta + gamma >= 1.0f )
		return false;
	
	float t = -( F*AKJB + E*JCAL + D*BLKC ) / denom;
	
	return ( t >= tmin and t <= tmax );
}