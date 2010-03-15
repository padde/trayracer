#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

// system header
#include <string>

// project header
#include <point.hpp>
#include <rgb.hpp>
#include <ray.hpp>
#include <shape.hpp>
#include <hitrecord.hpp>
#include <material.hpp>


//! @author Patrick Oscity
//! @date January 2010
//! @brief ... box class for depicting cubes in the scene
//
class Box : public Shape
{
public: // c'tors, d'tor
	Box ( std::string name, const Point& a, const Point& b, Material* material );
	~Box ();
	
public: // methods
	bool hit ( const Ray& ray, interval_t& tmin, HitRecord& hitrec ) const;
	bool hit ( const Ray& ray, interval_t& tmin ) const;
	
	Point a () const;
	Point b () const;
	
	void transform ( const Matrix& );
	
private: // member
	Point a_;
	Point b_;
};

#endif //BUW_BOX_HPP
