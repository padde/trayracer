#ifndef BUW_SPECULAR_HPP
#define BUW_SPECULAR_HPP

// project header
#include <brdf.hpp>
#include <hitrecord.hpp>
#include <vector.hpp>
#include <rgb.hpp>


//! @author Patrick Oscity
//! @date February 2010
//! @brief ... Advanced light model used for spot lighting
//
class Specular : public BRDF
{
public: // c'tors, d'tor 
	Specular ( const rgb& ks, const float& exp );
	~Specular();

	rgb f ( const HitRecord& sr, const Vector& wo, const Vector& wi ) const;

private: // member
	rgb   ks_;
	float exp_; // exponent
};

#endif //BUW_SPECULAR_HPP
