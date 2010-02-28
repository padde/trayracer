#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

// project header
#include <point.hpp>
#include <rgb.hpp>
#include <ray.hpp>
#include <shape.hpp>



class Box : public Shape
{
public: // c'tors, d'tor
	Box ();
	Box ( const Point& a, const Point& b );
	~Box ();
	
public: // methods
	bool hit ( const Ray& ray, interval_t tmin, interval_t tmax, HitRecord& hitrec ) const;
	bool hit ( const Ray& ray, interval_t tmin, interval_t tmax ) const;
	
private: // member
	Point a_;
	Point b_;
};

#endif //BUW_BOX_HPP