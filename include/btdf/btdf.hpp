#ifndef BUW_BTDF_HPP
#define BUW_BTDF_HPP

// project header
#include <rgb.hpp>
#include <hitrecord.hpp>


//! @author Patrick Oscity
//! @date February 2010
//! @brief ... bidirectional transmittance distribution function
//
class BTDF
{
public: // c'tors, d'tor
	BTDF();
	virtual ~BTDF();

public: // methods
	//! @brief returns the actual btdf rgb value
	//! @param wo omega out angle
	//! @param wi omega in angle
	virtual rgb  f        ( const HitRecord& hitrec, const Vector& wo, const Vector& wi ) const;
	//! @brief used for recursive calls
	//! @param wo omega out angle
	//! @param wi omega in angle
	virtual rgb  sample_f ( const HitRecord& hitrec, const Vector& wo,       Vector& wi ) const;
	//! @brief returns the bihemispherical reflectance
	//! @param wo omega out angle
	virtual rgb  rho      ( const HitRecord& hitrec, const Vector& wo                   ) const;
	//! @brief checks for total innner reflection
	virtual bool tir      ( const HitRecord& hitrec                                     ) const;
};

#endif
