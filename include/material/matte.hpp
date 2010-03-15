#ifndef BUW_MATTE_HPP
#define BUW_MATTE_HPP

// system header
#include <string>
#include <hitrecord.hpp>

// project header
#include <material.hpp>
#include <lambertian.hpp>


//! @author Patrick Oscity
//! @date January 2010
//! @brief ... Class for matte materials to drape shapes in
//
class Matte : public Material
{
public: // c'tors, d'tor
	Matte ( std::string name, const rgb ka, const rgb kd );
	~Matte();
	
public: // methods
	virtual rgb shade ( HitRecord& hitrec ) const;
	
private: // members
	Lambertian* ambient_brdf_ptr_;
	Lambertian* diffuse_brdf_ptr_;
	
};

#endif //BUW_MATTE_HPP
