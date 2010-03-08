#ifndef BUW_TRANSPARENT_HPP
#define BUW_TRANSPARENT_HPP

// system header
#include <string>

// project header
#include <rgb.hpp>
#include <phong.hpp>
#include <perfectspecular.hpp>
#include <perfecttransmitter.hpp>
#include <hitrecord.hpp>



class Transparent : public Phong
{
public: // c'tors, d'tor
	Transparent ( std::string name, const rgb ka, const rgb kd, const rgb ks, const float exp, const rgb kr, const float kt, const float ior );
	~Transparent();
	
public: // methods
	virtual rgb shade ( HitRecord& hitrec ) const;
	
private: // members
	PerfectSpecular*    reflective_brdf_ptr_;
	PerfectTransmitter* specular_btdf_ptr_;
};

#endif //BUW_REFLECTIVE_HPP