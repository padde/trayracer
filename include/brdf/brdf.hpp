#ifndef BUW_BRDF_HPP
#define BUW_BRDF_HPP

// project header
#include <rgb.hpp>
#include <vector.hpp>
#include <hitrecord.hpp>


//! @author Patrick Oscity
//! @date February 2010
//! @brief ... Bidirectional reflectance distribution function
//
class BRDF
{
public: // c'tors, d'tor
	BRDF();
	virtual ~BRDF();

public: // methods
	virtual rgb f        ( const HitRecord& hitrec, const Vector& wo, const Vector& wi ) const;
	virtual rgb sample_f ( const HitRecord& hitrec, const Vector& wo,       Vector& wi ) const;
	virtual rgb rho      ( const HitRecord& hitrec, const Vector& wo                   ) const;
};

#endif
