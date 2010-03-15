// i/f header
#include "triangle.hpp"

// project header
#include <box.hpp>

// system header
#include <cmath>



namespace { const float epsilon = 0.01; }



Triangle::Triangle ( std::string name, const Point& a, const Point& b, const Point& c, Material* material ) :
	Shape( name, material ),
	a_(a), b_(b), c_(c)
{
	float min_x = std::min( a_[0], std::min( b_[0], c_[0] ));
	float min_y = std::min( a_[1], std::min( b_[1], c_[1] ));
	float min_z = std::min( a_[2], std::min( b_[2], c_[2] ));
	float max_x = std::max( a_[0], std::max( b_[0], c_[0] ));
	float max_y = std::max( a_[1], std::max( b_[1], c_[1] ));
	float max_z = std::max( a_[2], std::max( b_[2], c_[2] ));
	
	bbox_.first  = Point(min_x,min_y,min_z);
	bbox_.second = Point(max_x,max_y,max_z);
}

Triangle::~Triangle ()
{}

bool Triangle::hit ( const Ray& original_ray, interval_t& tmin, HitRecord& hitrec ) const
{
	Ray ray = original_ray.transform(inv_trans_);
	
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
	
	if ( beta <= 0.0 or beta >= 1.0 )
		return false;
	
	float AKJB = A*K - J*B;
	float JCAL = J*C - A*L;
	float BLKC = B*L - K*C;
	
	float gamma = ( I*AKJB + H*JCAL + G*BLKC ) / denom;
	
	if ( gamma <= 0.0 or beta + gamma >= 1.0 )
		return false;
	
	float t = -( F*AKJB + E*JCAL + D*BLKC ) / denom;
	
	if ( t < tmin and t > epsilon)
	{
		// hit detected
		tmin                = t;
		hitrec.t            = t;
		hitrec.hit          = true;
		hitrec.normal       = unify(back_trans_ * cross(Vector(b_-a_), Vector(c_ - a_)));
		hitrec.material_ptr = material_ptr_;
		hitrec.hitpoint     = (back_trans_ * ray.origin()) + t * (back_trans_ * ray.dir());
		hitrec.ray          = original_ray;
		
		return true;
	}
	
	return false;
}

bool Triangle::hit ( const Ray& original_ray, interval_t& tmin ) const
{
	Ray ray = original_ray.transform(inv_trans_);
	
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
	
	if ( beta <= 0.0 or beta >= 1.0 )
		return false;
	
	float AKJB = A*K - J*B;
	float JCAL = J*C - A*L;
	float BLKC = B*L - K*C;
	
	float gamma = ( I*AKJB + H*JCAL + G*BLKC ) / denom;
	
	if ( gamma <= 0.0 or beta + gamma >= 1.0 )
		return false;
	
	float t = -( F*AKJB + E*JCAL + D*BLKC ) / denom;
	
	if ( t > epsilon )
	{
		tmin = t;
		return true;
	}
	
	return false;
}