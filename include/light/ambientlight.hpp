#ifndef BUW_AMBIENTLIGHT_HPP
#define BUW_AMBIENTLIGHT_HPP

// system header
#include <string>

// project header
#include <rgb.hpp>
#include <vector.hpp>
#include <hitrecord.hpp>
#include <light.hpp>


//! @author Patrick Oscity
//! @date January 2010
//! @brief ... Ambient light source class
//
class AmbientLight : public Light
{
public: // c'tors, d'tor
	AmbientLight ( std::string name, rgb ls );
	~AmbientLight();
	
public: // methods
	Vector get_direction ( HitRecord& hitrec ) const;
	rgb    L             ( HitRecord& hitrec ) const;

private: // private members
	rgb   ls_;
};

#endif //BUW_AMBIENTLIGHT_HPP
