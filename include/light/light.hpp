#ifndef BUW_LIGHT_HPP
#define BUW_LIGHT_HPP

// system header
#include <string>

// project header
#include <rgb.hpp>
#include <vector.hpp>
#include <point.hpp>
#include <hitrecord.hpp>



class Light
{
public: // c'tors, d'tor
	Light ( std::string name );
	~Light();
	
public: // methods
	virtual Vector get_direction ( HitRecord& hitrec ) const = 0;
	virtual rgb    L             ( HitRecord& hitrec ) const = 0;
	virtual bool   in_shadow     ( const Ray& ray, const HitRecord& hitrec ) const;
	virtual Point  position      () const;
	
	std::string name () const;

private: // private members
	std::string name_;
};

#endif //BUW_LIGHT_HPP