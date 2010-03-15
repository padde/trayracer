#ifndef BUW_POINTLIGHT_HPP
#define BUW_POINTLIGHT_HPP

// system header
#include <string>

// project header
#include <rgb.hpp>
#include <vector.hpp>
#include <hitrecord.hpp>
#include <light.hpp>


//! @author Patrick Oscity
//! @date January 2010
//! @brief ... Point light source class
//
class PointLight : public Light
{
public: // c'tors, d'tor
	PointLight ( std::string name, Point position, rgb ls );
	~PointLight();

public: // methods
	Vector get_direction ( HitRecord& hitrec ) const;
	rgb    L             ( HitRecord& hitrec ) const;
	bool   in_shadow     ( const Ray& ray, const HitRecord& hitrec ) const;
	Point  position      () const;

private: // members
	rgb    ls_;
	Point  position_;
};

#endif //BUW_POINTLIGHT_HPP
