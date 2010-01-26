#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

// system header
#include <string>

// project header
#include <rgb.hpp>
#include <ray.hpp>
// #include <material.hpp>
class Material; // FIXME: uncomment above line and delete this one, when material is implemented



// struct for recording hits
struct HitRecord
{
	bool   hit;
	float  t;
	rgb    color;
	Vector normal;
};



class Shape
{
public: // enums, typedefs
	typedef float interval_t;

public: // c'tors, d'tor
	Shape ();
	Shape ( std::string name, Material* material );
	virtual ~Shape ();

public: // methods
	const std::string& name () const;

public: // virtual methods
	virtual bool hit        ( const Ray& ray, interval_t tmin, interval_t tmax, HitRecord& hitrec ) const = 0;
	virtual bool shadow_hit ( const Ray& ray, interval_t tmin, interval_t tmax ) const = 0;

private:
	std::string name_;
	Material*   material_;
};

#endif //BUW_SHAPE_HPP 