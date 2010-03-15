#ifndef BUW_PHONG_HPP
#define BUW_PHONG_HPP

// system header
#include <string>
#include <hitrecord.hpp>

// project header
#include <material.hpp>
#include <lambertian.hpp>
#include <specular.hpp>


//! @author Patrick Oscity
//! @date January 2010
//! @brief ... Class for materials with ambient, diffuse and specular lighting
//
class Phong : public Material
{
public: // c'tors, d'tor
	Phong ( std::string name, const rgb ka, const rgb kd, const rgb ks, const float exp );
	~Phong();
	
public: // methods
	virtual rgb shade ( HitRecord& hitrec ) const;
	
private: // members
	Lambertian* ambient_brdf_ptr_;
	Lambertian* diffuse_brdf_ptr_;
	Specular*  specular_brdf_ptr_;
};

#endif //BUW_PHONG_HPP
