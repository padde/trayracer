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
	Lambertian ( const rgb& kd );
	~Lambertian();

	rgb f ( const HitRecord& sr, const Vector& wo, const Vector& wi ) const;
	rgb rho ( const HitRecord& sr, const Vector& wo ) const;

private: // member
	rgb kd_; // diffuse coefficient
};

#endif //BUW_LAMBERTIAN_HPP
