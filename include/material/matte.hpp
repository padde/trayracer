#ifndef BUW_MATTE_HPP
#define BUW_MATTE_HPP

// system header
#include <string>
#include <hitrecord.hpp>

// project header
#include <material.hpp>
#include <lambertian.hpp>



class Matte : public Material
{
public: // c'tors, d'tor
	Matte ( std::string name, const float ka, const float kd, const rgb cd );
	~Matte();
	
public: // methods
	virtual rgb shade ( HitRecord& hitrec ) const;
	
private: // members
	Lambertian* ambient_brdf_ptr_;
	Lambertian* diffuse_brdf_ptr_;
	
};

#endif //BUW_MATTE_HPP