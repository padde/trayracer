#ifndef BUW_TRIANGLE_HPP
#define BUW_TRIANGLE_HPP

// system header
#include <string>

// project header
#include <point.hpp>
#include <rgb.hpp>
#include <ray.hpp>
#include <shape.hpp>
#include <hitrecord.hpp>
#include <material.hpp>



class Triangle : public Shape
{
public: // c'tors, d'tor
	Triangle ( std::string name, const Point& a, const Point& b, const Point& c, Material* material );
	~Triangle ();
	
public: // methods
	bool hit ( const Ray& ray, interval_t tmin, interval_t tmax, HitRecord& hitrec ) const;
	bool hit ( const Ray& ray, interval_t tmin, interval_t tmax ) const;
	
private: // member
	Point a_;
	Point b_;
	Point c_;
};

#endif //BUW_TRIANGLE_HPP 