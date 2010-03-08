#ifndef BUW_BTDF_HPP
#define BUW_BTDF_HPP

// project header
#include <rgb.hpp>
#include <hitrecord.hpp>



class BTDF
{
public: // c'tors, d'tor
	BTDF();
	virtual ~BTDF();

public: // methods
	virtual rgb  f        ( const HitRecord& hitrec, const Vector& wo, const Vector& wi ) const;
	virtual rgb  sample_f ( const HitRecord& hitrec, const Vector& wo,       Vector& wi ) const;
	virtual rgb  rho      ( const HitRecord& hitrec, const Vector& wo                   ) const;
	virtual bool tir      ( const HitRecord& hitrec                                     ) const;
};

#endif
