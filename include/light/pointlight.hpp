#ifndef BUW_POINTLIGHT_HPP
#define BUW_POINTLIGHT_HPP

// system header
#include <string>

// project header
#include <rgb.hpp>
#include <vector.hpp>
#include <hitrecord.hpp>
#include <light.hpp>



class PointLight : public Light
{
public: // c'tors, d'tor
	PointLight ( std::string name );
	PointLight ( std::string name, float ls, rgb color, Point position );
	~PointLight();
	
public: // methods
	Vector get_direction ( HitRecord& hitrec ) const;
	rgb    L             ( HitRecord& hitrec ) const;

private: // private members
	float  ls_;
	rgb    color_;
	Point  position_;
};

#endif //BUW_POINTLIGHT_HPP