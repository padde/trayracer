#ifndef BUW_AMBIENTLIGHT_HPP
#define BUW_AMBIENTLIGHT_HPP

// system header
#include <string>

// project header
#include <rgb.hpp>
#include <vector.hpp>
#include <hitrecord.hpp>
#include <light.hpp>



class AmbientLight : public Light
{
public: // c'tors, d'tor
	AmbientLight ( std::string name );
	AmbientLight ( std::string name, rgb ls );
	~AmbientLight();
	
public: // methods
	Vector get_direction ( HitRecord& hitrec ) const;
	rgb    L             ( HitRecord& hitrec ) const;

private: // private members
	float ls_;
	rgb   color_;
};

#endif //BUW_AMBIENTLIGHT_HPP