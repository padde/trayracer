#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

// project header
#include <point.hpp>
#include <rgb.hpp>
#include <ray.hpp>
#include <shape.hpp>
// #include <material.hpp>


class Sphere : public Shape
{
public: // c'tors, d'tor
	Sphere ();
	Sphere ( const float& radius );
	~Sphere ();
	
public: // methods
	bool hit ( const Ray& ray, interval_t tmin, interval_t tmax, HitRecord& hitrec ) const;
	bool hit ( const Ray& ray, interval_t tmin, interval_t tmax ) const;
	
private:
	float radius_;
};

#endif //BUW_SPHERE_HPP 