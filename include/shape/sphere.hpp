#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

// system header
#include <string>

// project header
#include <point.hpp>
#include <rgb.hpp>
#include <ray.hpp>
#include <shape.hpp>
#include <hitrecord.hpp>
#include <material.hpp>



class Sphere : public Shape
{
public: // c'tors, d'tor
	Sphere ( std::string name, const Point& center, const float& radius, Material* material );
	~Sphere ();
	
public: // methods
	bool hit ( const Ray& ray, interval_t tmin, interval_t tmax, HitRecord& hitrec ) const;
	bool hit ( const Ray& ray, interval_t tmin, interval_t tmax ) const;
	
private:
	float radius_;
	Point center_;
};

#endif //BUW_SPHERE_HPP 