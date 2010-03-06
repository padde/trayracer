#ifndef BUW_PERFECTSPECULAR_HPP
#define BUW_PERFECTSPECULAR_HPP

// project header
#include <rgb.hpp>
#include <hitrecord.hpp>
#include <brdf.hpp>



class PerfectSpecular : public BRDF
{
public: // c'tors, d'tor
	PerfectSpecular ( const float& kr, const rgb& cr );
	~PerfectSpecular ();

public: // methods
	rgb sample_f ( const HitRecord& hitrec, const Vector& wo, Vector& wi ) const;
	
	void kr ( const float kr );
	void cr ( const rgb&  cr );
	
	float kr () const;
	rgb   cr () const;

private: // member
	float kr_;
	rgb   cr_;
};

#endif //BUW_PERFECTSPECULAR_HPP
