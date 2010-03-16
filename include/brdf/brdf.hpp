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
	//! @brief returns the actual brdf rgb value
	//! @param wo omega out angle
	//! @param wi omega in angle
	virtual rgb f        ( const HitRecord& hitrec, const Vector& wo, const Vector& wi ) const;
	//! @brief used for reflectance
	//! @param wo omega out angle
	//! @param wi omega in angle
	virtual rgb sample_f ( const HitRecord& hitrec, const Vector& wo,       Vector& wi ) const;
	//! @brief returns the bihemispherical reflectance
	//! @param wo omega out angle
	virtual rgb rho      ( const HitRecord& hitrec, const Vector& wo                   ) const;
};

#endif
