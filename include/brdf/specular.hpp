#ifndef BUW_SPECULAR_HPP
#define BUW_SPECULAR_HPP

// project header
#include <brdf.hpp>
#include <hitrecord.hpp>
#include <vector.hpp>
#include <rgb.hpp>



class Specular : public BRDF
{
public: // c'tors, d'tor 
	Specular ();
	Specular ( const float& ks, const rgb& cs, const float& exp );
	~Specular();

	rgb f   ( const HitRecord& sr, const Vector& wo, const Vector& wi ) const;
	rgb rho ( const HitRecord& sr, const Vector& wo ) const;

	void ks  ( const float ks );
	void exp ( const float e  );
	void cs  ( const rgb&  cs );
		
	float ks  () const;
	float exp () const;
	rgb   cs  () const;

private: // member
	float ks_;
	float exp_; // exponent
	rgb   cs_;  // color
};

#endif //BUW_SPECULAR_HPP
