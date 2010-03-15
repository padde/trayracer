#ifndef BUW_LAMBERTIAN_HPP
#define BUW_LAMBERTIAN_HPP

// project header
#include <brdf.hpp>
#include <hitrecord.hpp>
#include <vector.hpp>
#include <rgb.hpp>


//! @author Patrick Oscity
//! @date February 2010
//! @brief ... Light model used for diffuse lighting
//
class Lambertian : public BRDF
{
public: // c'tors, d'tor
	Lambertian ( const rgb& kd );
	~Lambertian();

	//! @brief Returns the BRDF itself
	rgb f ( const HitRecord& sr, const Vector& wo, const Vector& wi ) const;
	rgb rho ( const HitRecord& sr, const Vector& wo ) const;

private: // member
	//! @brief diffuse coefficient
	rgb kd_; 
};

#endif //BUW_LAMBERTIAN_HPP
