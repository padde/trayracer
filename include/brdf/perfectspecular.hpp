#ifndef BUW_PERFECTSPECULAR_HPP
#define BUW_PERFECTSPECULAR_HPP

// project header
#include <rgb.hpp>
#include <vector.hpp>
#include <hitrecord.hpp>
#include <brdf.hpp>



class PerfectSpecular : public BRDF
{
public: // c'tors, d'tor
	PerfectSpecular ( const rgb& kr );
	~PerfectSpecular ();

public: // methods
	rgb sample_f ( const HitRecord& hitrec, const Vector& wo, Vector& wi ) const;

private: // member
	rgb kr_;
};

#endif //BUW_PERFECTSPECULAR_HPP
