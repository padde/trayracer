#ifndef BUW_PHONG_HPP
#define BUW_PHONG_HPP

// system header
#include <string>
#include <hitrecord.hpp>

// project header
#include <material.hpp>
#include <lambertian.hpp>
#include <specular.hpp>



class Phong : public Material
{
public: // c'tors, d'tor
	Phong ( std::string name, const float ka, const float kd, const float ks, const float exp, const rgb cd );
	~Phong();
	
public: // methods
	virtual rgb shade ( HitRecord& hitrec ) const;
	
private: // members
	Lambertian* ambient_brdf_ptr_;
	Lambertian* diffuse_brdf_ptr_;
	Specular*  specular_brdf_ptr_;
};

#endif //BUW_PHONG_HPP