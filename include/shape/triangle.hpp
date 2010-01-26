#ifndef BUW_TRIANGLE_HPP
#define BUW_TRIANGLE_HPP

// project header
#include <point.hpp>
#include <rgb.hpp>
#include <ray.hpp>
#include <shape.hpp>
// #include <material.hpp>



class Triangle : public Shape
{
public: // c'tors, d'tor
	Triangle ();
	Triangle ( const Point& a, const Point& b, const Point& c );
	~Triangle ();
	
public: // methods
	bool hit        ( const Ray& ray, interval_t tmin, interval_t tmax, HitRecord& hitrec ) const;
	bool shadow_hit ( const Ray& ray, interval_t tmin, interval_t tmax ) const;
	
private: // member
	Point a_;
	Point b_;
	Point c_;
};

#endif //BUW_TRIANGLE_HPP 