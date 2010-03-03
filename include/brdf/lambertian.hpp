#ifndef BUW_LAMBERTIAN_HPP
#define BUW_LAMBERTIAN_HPP

// project header
#include <brdf.hpp>
#include <hitrecord.hpp>
#include <vector.hpp>
#include <rgb.hpp>



class Lambertian : public BRDF
{
public: // c'tors, d'tor 
	Lambertian ();
	Lambertian ( const float& kd, const rgb& cd );
	~Lambertian();

	rgb f   ( const HitRecord& sr, const Vector& wo, const Vector& wi ) const;
	rgb rho ( const HitRecord& sr, const Vector& wo ) const;

	void ka ( const float ka );
	void kd ( const float kd );
	void cd ( const rgb&  cd );
		
	float ka () const;
	float kd () const;
	rgb   cd () const;

private: // member
	float kd_; // diffuse coefficient
	rgb   cd_; // color
};

#endif //BUW_LAMBERTIAN_HPP
