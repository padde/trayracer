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


//! @author Patrick Oscity
//! @date January 2010
//! @brief ... special type of phong for materials with glasslike attributes
//! @image html Figure27.04.png
//! @image html Figure27.05.png
//! @image html Figure27.06.png
//! @image html Figure27.08.png
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
